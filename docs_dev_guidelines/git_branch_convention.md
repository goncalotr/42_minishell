# Git Branch Naming Guidelines

This guide outlines a convention for naming Git branches, inspired by the Conventional Branch specification. Adopting a standard format improves clarity, organization, and automation within the project workflow.

## 1 Intro

Consistent branch naming makes it easier for everyone on the team (and your future self!) to understand the purpose of a branch at a glance. It also helps integrate with automated tools and processes (like CI/CD, if applicable).

This convention uses a `<type>/<description>` format.

## 2 Branch Naming Format

Branch names should follow this structure:

```bash
<type>/<description>
```

Where:
- **`<type>`:** Indicates the *kind* of work being done in the branch (mandatory).
- **`<description>`:** A short, descriptive summary of the branch's purpose (mandatory).

**Example:**

```sh
# Creating a new branch for adding the 'cd' command
git checkout -b feature/add-cd-builtin

# Creating a branch to fix a parsing error
git checkout -b bugfix/fix-parser-segfault
```

## 3 Branch Parts
### 3.1 Types

Must be one of the following prefixes, followed by a /:

- **feature/**: For developing a new feature for the minishell (e.g., adding a new builtin, implementing pipes).
- **bugfix/**: For fixing a bug in the code (e.g., correcting a memory leak, fixing incorrect command execution).
- **hotfix/**: For critical, urgent fixes that need to be deployed quickly (less common in student projects, but good practice). Often branched from main/master.
- **release/**: For preparing a new release version (e.g., finalizing features, bumping versions). Often branched from develop if used, or main.
- **chore/**: For tasks that don't directly change production code but are necessary for the project (e.g., updating documentation, configuring CI, updating dependencies, refactoring build scripts).

Note on Base Branches: Standard base branches like main, master, or develop do not use this prefix format. This convention applies to branches created from these base branches for specific tasks.

### 3.2 Description

The description provides context about the branch's purpose:

- **Use lowercase alphanumeric characters (a-z, 0-9) and hyphens (-) only.**
- **Separate words with hyphens (-).** Do not use underscores (_) or spaces.
- **Keep it concise and descriptive.** Clearly indicate the work being done.
- **Do not use consecutive hyphens (--) or trailing hyphens (-).**
- **Optional:** Include an issue/ticket number if you are using an issue tracker (e.g., feature/42-implement-redirections).

## 4 Basic Rules Summary

- **Format:** Always use <type>/<description>.
- **Casing:** Use lowercase only.
- **Separators:** Use hyphens (-) to separate words in the description.
- **Characters:** Only a-z, 0-9, and - are allowed.
- **Clarity:** Be descriptive but brief.
- **Hyphens:** No consecutive (--) or trailing (-) hyphens.

## 5 Examples
### Feature Branches

```sh
# Adding support for environment variable expansion
git checkout -b feature/implement-env-expansion

# Adding the 'export' builtin command
git checkout -b feature/add-export-builtin
```

### Bugfix Branches

```sh
# Fixing a segmentation fault when input is empty
git checkout -b bugfix/fix-empty-input-segfault

# Correcting redirection file descriptor handling
git checkout -b bugfix/correct-fd-redirection
```

### Chore Branches

```sh
# Updating the README with usage examples
git checkout -b chore/update-readme-examples

# Adding a Makefile rule for code linting
git checkout -b chore/add-linting-rule
```

### Release Branches (If applicable)

```sh
# Preparing for version 0.1.0 release
git checkout -b release/v0.1.0
```

## 6 Benefits

- Clarity: Instantly understand the purpose of any branch.
- Consistency: Standardizes workflow across the project/team.
- Organization: Easier to navigate and manage branches.
- Automation: Enables potential automation based on branch types (e.g., running specific tests for bugfix/ branches).

## 7 Reference

- https://conventional-branch.github.io/
