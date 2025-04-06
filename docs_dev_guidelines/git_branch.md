# Branch Related Commands

## Commands


### Create branch

```sh
git branch feature/new-feature
```

### Switch branch

```sh
git checkout feature/new-feature
```
or, with a new command
```sh
git switch feature/new-feature
```

Switch to new branch (create and change to it)
```sh
git checkout -b feature/new-feature
```

```sh
git switch -c feature/new-feature
```
### List branches

```sh
git checkout -b feature/new-feature
```

### Merge current branch
```sh
git merge feature/new-feature
```


### Delete branch

Locally
```sh
git branch -d feature/new-feature  # Use -D to force delete
```
Remotely
```sh
git push origin --delete feature/new-feature
```

Push a new branch to a remote repository:
```sh
git push -u origin feature/new-feature
```
### Retrieve latest changes from a remote repository

Fetch and check out a remote branch:
```sh
git fetch origin
git checkout -b feature/new-feature origin/feature/new-feature
```

#### git fetch
git fetch is a command that retrieves the latest changes from a remote repository without merging them into your local branch. It allows you to see updates made by others before deciding to integrate them.

##### Comparison

|Command|What it does|When to use|
|----|-----|---|
|git fetch|Downloads new commits, branches, and tags from the remote but does not merge them into your local branch.|When you want to check for updates without applying them immediately.|
|git pull|Fetches remote changes and automatically merges them into your current branch.|When you want to immediately update your local branch with the latest remote changes.|


##### Basic Usage of git fetch

Fetch all remote changes without merging:

```sh
git fetch origin
```

This updates your local copy of remote branches but does not change your working branch.

Fetch a specific branch:

```sh
git fetch origin feature/new-feature
```

This retrieves updates for feature/new-feature but does not switch to it.

Check fetched changes:

```sh
git log origin/main --oneline
```

This shows the latest commits on origin/main after fetching.

Update your branch after fetching:

```sh
git merge origin/main
```

This applies the fetched changes to your local branch manually.

Fetch and switch to a remote branch:

```sh
git fetch origin
git checkout -b feature/new-feature origin/feature/new-feature
```

This creates a local copy of a remote branch and switches to it.


## Key Commands Summary:
- `git checkout <branch_name>`: Switch to an existing branch.
- `git pull origin <branch_name>`: Fetch from remote and merge into local branch.
- `git checkout -b <new_branch_name>`: Create a new branch and switch to it. Alternative:`git switch -b <new_branch_name>`, this option is more recent and only used for branch switching.
- `git add <file(s)>`: Stage changes for commit.
- `git commit -m "..."`: Commit staged changes.
- `git merge <branch_to_merge_in>`: Merge the specified branch into your current branch.
- `git push origin <branch_name>`: Push your local branch commits to the remote.
- `git branch -d <branch_name>`: Delete a merged local branch.
- `git push origin --delete <branch_name>`: Delete a remote branch.
- `git fetch origin`: Download objects and refs from the remote repository without merging.















## Examples

### 1. Creating a New Feature Branch

This is the standard way to start working on a new feature or task in isolation.

**Steps:**

1. **Ensure 'main' is up-to-date:** Before creating a new branch, make sure your local `main` branch has the latest changes from the remote repository.

	```sh
	# Switch to your main branch (e.g., 'main' or 'master')
	git switch main

	# Pull the latest changes from GitHub
	git pull origin main
	```

2. **Create and switch to the new branch:** Choose a descriptive name for your branch (e.g., `feature/new-parser`, `fix/memory-leak`).

	```sh
	# Creates the new branch based on the current state of 'main' and switches to it
	git switch -c feature/your-new-feature-branch

	# --- Now you can start working on your feature ---
	```

### 2. Updating an Existing Branch with Changes from 'main'

If you have an existing branch (like `implement/core-loop`) that you started earlier, and `main` has been updated since then (e.g., other features or documentation were merged), you need to bring those updates into your branch.

**Choose ONE of the following methods:**

**Method A: Using `git merge` (Recommended for simplicity)**

This adds the changes from `main` into your branch and creates a "merge commit".

1. **Switch to the branch you want to update:**
	```sh
	git switch implement/core-loop
	```

2.  **Fetch the latest remote changes:** Ensures your Git knows about the newest `origin/main`.

	```sh
	git fetch origin
	```

3.  **Merge the latest `main` into your current branch:**

	```sh
	git merge origin/main
	```
	- *Git will create a merge commit. Resolve conflicts if prompted.*

**Method B: Using `git rebase` (Cleaner history, use with caution)**

This replays your branch's unique commits *on top of* the latest `main`. **Warning:** This rewrites history. Don't use it on branches others have pulled or branched from.

1. **Switch to the branch you want to update:**

	```sh
	git switch implement/core-loop
	```

2. **Fetch the latest remote changes:**

	```sh
	git fetch origin
	```

3. **Rebase your branch onto the latest `main`:**

	```sh
	git rebase origin/main
	```
	- *Your commits will be reapplied. Resolve conflicts if prompted.*

**Method C: Resetting Branch to Match 'main' (Discarding Local Changes)**

Use this **only** if you want to completely discard any unique commits or changes on your local branch (`implement/core-loop` in this example) and make it identical to the latest `main`. **WARNING: This is destructive to local work on that branch.**

1. **Switch to the branch you want to reset:**

	```sh
	git switch implement/core-loop
	```

2. **Fetch the latest remote changes:**

	```sh
	git fetch origin
	```

3. **Hard reset the branch to match `origin/main`:**
	```bash
	# WARNING: Deletes unique local commits/changes on this branch!
	git reset --hard origin/main
	```
