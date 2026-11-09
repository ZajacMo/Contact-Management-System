# Contact Management System

*[Chinese](README_CN.md)*

> **Repository status: archived.**
> This is a completed 2022 course project, kept for reference. It is no longer
> developed. See the [Archive notice](#archive-notice) at the end of this
> document for what was changed before archiving, and what was deliberately
> left alone.

A Windows desktop contact manager built with **MFC** (Microsoft Foundation
Classes). It provides password-protected sign-in, a contact list, add / view /
modify / delete operations, and file-based persistence.

## Table of contents

- [Features](#features)
- [Screens and workflow](#screens-and-workflow)
- [Building](#building)
- [Running](#running)
- [Project structure](#project-structure)
- [Data format](#data-format)
- [Password storage](#password-storage)
- [Known limitations](#known-limitations)
- [Archive notice](#archive-notice)
- [License](#license)

## Features

- **Sign-in with password** - the stored password is obfuscated, not kept in
  plain text. A first run with no password file creates one instead of
  rejecting the input.
- **Contact list** - shows the number, name and phone of every contact, sorted
  by descending age.
- **Add a contact** - name and phone number are required, the age is optional
  but must be a whole number, and duplicates are rejected.
- **View, modify and delete** - a detail dialog shows every field and can
  update or remove the record.
- **Change the password** - requires the current password.
- **Clear all contacts** - empties the list after a confirmation.
- **Persistent storage** - contacts are written to `contact.txt` and reloaded on
  the next launch.

## Screens and workflow

The application opens on the sign-in dialog:

```
+---------------------------------------------+
|        Contact Manager 1.11                 |
|                                             |
|   Welcome to Contact Manager 1.11           |
|                                             |
|        Enter your password:                 |
|        [_____________________]              |
|                                             |
|   [x] I have read the security agreement    |
|                        [ Sign in ] [ Exit ] |
+---------------------------------------------+
```

Tick the agreement box, type the password and press **Sign in** (or Enter).
With no `secret.txt` present, the first password you type becomes the stored
password.

The main window lists the contacts and offers **New**, **Details**, **Clear**,
**Password** and **Save**:

```
+------------------------------------------------------+
|  Contact Manager 1.11                                |
|  Number of contacts: 3                               |
|  +------+-------------+--------------+               |
|  | No.  | Name        | Phone        |               |
|  +------+-------------+--------------+               |
|  | 1    | Bob         | 119          |               |
|  | 2    | Alice       | 110          |               |
|  | 3    | Carol       | 120          |               |
|  +------+-------------+--------------+               |
|                              [ New ] [ Details ]     |
|                              [ Clear ] [ Password ]  |
|                              [ Save ]                |
+------------------------------------------------------+
```

Selecting a row and pressing **Details** opens the detail dialog, which has
**Modify** and **Delete** buttons. Pressing **Save** writes the list to
`contact.txt` and exits.

## Building

### Requirements

| Requirement | Version |
|---|---|
| Operating system | Windows 10 or later |
| Visual Studio | 2019 or later (2022 recommended) |
| Toolset | v143 (the `PlatformToolset` in `MFCApplication1.vcxproj`) |
| MFC | **Required** - install the "C++ MFC for latest v143 build tools" component |
| Windows SDK | 10.0 or later |

MFC is not part of a default Visual Studio installation. Without the MFC
component the build fails with:

```
error MSB8041: This project requires the MFC library.
```

### With Visual Studio

1. Open `MFCApplication1.vcxproj` (or the solution `通讯录1.11.sln`).
2. Pick a configuration: `Debug` or `Release`, `x86` or `x64`.
3. Build with **Build > Build Solution**.
4. The executable is written to `Debug\` or `Release\`.

The solution file name contains Chinese characters. If your checkout path
causes trouble with the toolchain, open `MFCApplication1.vcxproj` directly
instead - it does not depend on the solution.

### Source encoding

All `.cpp` and `.h` files are **UTF-8 with BOM**, which MSVC detects
automatically. The resource script `MFCApplication1.rc` is **UTF-16 LE with
BOM**, the format the Resource Editor writes.

## Running

The program reads and writes two files **in the current working directory**:

| File | Purpose |
|---|---|
| `contact.txt` | The contact list. Created on the first save. |
| `secret.txt` | The obfuscated login password. Created on the first sign-in. |

Run the executable from the directory you want those files to live in. Running
it from the build output directory is fine; just remember that `contact.txt`
is *not* version controlled.

If you forget the password, delete `secret.txt` and sign in again - the next
password you type becomes the new one. There is no recovery mechanism, and
the stored password cannot be read back in plain text.

## Project structure

```
contact.h           # contact and ContactList: the data model and persistence
lock.h              # password obfuscation and edit-control helpers
MFCApplication1.*   # application object, startup, and the shared list instance
MFCApplication1Dlg.*# sign-in dialog
MENU.*              # main window: the contact list and the action buttons
DIALOG_ADD.*        # "New Contact" dialog
DIALOG_DETAIL.*     # "Contact Details" dialog
DIALOG_CODE.*       # "Password Management" dialog
SIGNSUCCESS.*       # transient notification dialog
MFCApplication1.rc  # dialog layouts and UI strings
resource.h          # resource identifiers
res/                # icon and non-editable resource fragments
```

### Core types

**`contact`** - one record. The fields are private and reached through the
`f_*()` accessors. `ContactList` is a friend so it can fill records directly
while reading from disk.

**`ContactList`** - the collection. It holds a fixed array of 1000 slots.
A free slot is marked by `age == -1`, which is why the age is validated as a
non-negative whole number when a contact is created.

`ContactList::line()` sorts the contacts by descending age and returns how many
slots are in use. Because free slots carry age `-1`, they sort to the end, so
occupied contacts always occupy the indices `[0, count)`. That ordering is
what the list view shows and what `SaveContact()` writes, so it is part of the
observable behaviour rather than an implementation detail.

## Data format

`contact.txt` is a tab-separated text file, one record per line:

```
name <TAB> phone <TAB> sex <TAB> age <TAB> address
```

The list is terminated by a sentinel record whose first field is `off`:

```
Bob	119	M	40	Addr B
Carol	120	F	20	Addr C
off	1	1	-1	1
```

Details:

- **Only the tab is a separator.** Fields may contain spaces; `Alice Smith`
  is read back correctly.
- **`-1` means "not set"** for the optional `sex` and `address` fields. It is
  loaded back as an empty string.
- **The `off` sentinel terminates the list.** Anything after it is ignored.
- The file is written in the same descending-age order the list view shows.

## Password storage

The password is not stored in plain text. `lock.h` defines a monalphabetic
substitution over a 62-character alphabet:

```cpp
const char ArrSecret[]  = "qwertyuiHIJKLMNop[ABCDEFG]asdUVWXYZfghjkOPQRSTl;zxcvbnm,.?{}:|";
const char ArrObvious[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890abcdefghijklmnopqrstuvwxyz";
```

`ArrSecret[i]` and `ArrObvious[i]` are two views of the same permutation.
`setcode()` maps each character of the plain text through `ArrObvious` into
`ArrSecret` and writes the result to `secret.txt`; `checkcode()` maps the
stored characters back and compares them against the entered password.

For example, the password `123456` is stored as `asdUVW`.

**This is obfuscation, not encryption.** The substitution table is compiled
into the executable and readable in the source, so anyone who can read the
binary can recover the password. The point is only to keep the plain text out
of `secret.txt`. Do not rely on it to protect anything sensitive.

Passwords are restricted to the 62 characters of the alphabet above. A
character outside it is rejected when the password is set rather than being
silently dropped - a dropped character would produce a stored password that no
longer matches what the user typed.

## Known limitations

These are inherent to the original design and were **not** changed when the
repository was archived. They are listed here so that nobody is surprised.

- **The password protection is not real security.** See
  [Password storage](#password-storage).
- **Non-ASCII names depend on the system code page.** The dialog text is
  converted through `CStringA`, so a name in Chinese, Japanese or any other
  non-ANSI script depends on the machine's regional settings.
- **The list is capped at 1000 contacts.** The cap is a compile-time constant.
- **Contacts are always ordered by descending age.** There is no way to sort
  by name or phone number.
- **There is no undo.** **Clear** empties the list immediately; the only
  recovery is the last saved `contact.txt`.
- **The contact list is only written when you press Save.** Closing the window
  without saving discards the changes.
- **`age` doubles as the free-slot marker.** A contact with an age of `0` is
  valid, but the detail dialog does not display a zero age, because the
  original code used `0` to mean "not set".

## Archive notice

The repository was archived on 2026-11-10. The following changes were made
immediately before archiving, so that the project is at least buildable and
readable:

**Fixed**

- All sources converted to UTF-8 with BOM and all comments and UI strings
  translated to English. The repository previously mixed GBK, UTF-8 and UTF-16
  files, and the README rendered as mojibake on GitHub.
- **Multiple definition linker errors.** `ContactList List`, `setcode`,
  `checkcode`, `informationget`, `Tip_m` and `Tip_s` were defined in headers,
  giving every translation unit its own copy. The link only succeeded because
  `/FORCE` was set. These are now `inline` or have a single definition.
- **Memory leaks.** Three `new char[]` allocations in the sign-in and password
  dialogs were never freed.
- **Unbounded file read.** `ReadContact()` incremented its index without a
  limit, so a corrupt `contact.txt` could write past the end of the array.
- **Unchecked file handles.** `fopen` results were never checked, so a missing
  `secret.txt` crashed the program instead of reporting a missing password.
- **File I/O via `freopen`.** Reading and writing the contact file by
  redirecting `stdin` and `stdout` was replaced with `std::fstream`.
- **Hard exits.** `exit(0)` skipped destructors and discarded unsaved data.
- **The repository could not be built from a clone.** The `.gitignore`
  excluded `*.sln`, `*.vcxproj` and `*.rc` - precisely the files needed to
  build an MFC project. Those files are now tracked.
- **A stale solution reference.** The solution referenced a project whose
  directory no longer exists, which made the solution fail to load. It has been
  removed.
- **A filename case mismatch.** The project referenced `Resource.h` while the
  file on disk is `resource.h`.
- **1.4 MB of Visual Studio temporary files** (`RCa*` / `RD*` resource editor
  leftovers) were removed from version control.

**Verified**

The rewritten data model and password code were compiled with MSVC 19.44 and
exercised against a test harness: password round-trips, contact insertion,
the descending-age ordering, search by name and by phone number, deletion,
the save/load round trip, the `-1` "not set" convention, and the missing-file
case all behave as documented above. Existing `secret.txt` files still unlock
with the password they were created with.

**Deliberately not changed**

- The MFC framework itself, the fixed 1000-slot array, and the descending-age
  ordering.
- The substitution cipher. Replacing it with a real KDF would change the
  on-disk format and lock existing users out.
- The GUI layout and the resource script's dialog definitions.

**Not verified**

The GUI was **not** compiled or run: MFC is not installed in the environment
used for the archive, and the Visual Studio build fails with `MSB8041` before
reaching the compiler. The data model and the password code were verified by
compiling them directly against stub MFC types, but the dialog wiring itself
is untested.

## License

MIT - see [LICENSE](LICENSE).
