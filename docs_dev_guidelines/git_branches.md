#

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

Fetch and check out a remote branch:
```sh
git fetch origin
git checkout -b feature/new-feature origin/feature/new-feature
```

git fetch

git fetch is a command that retrieves the latest changes from a remote repository without merging them into your local branch. It allows you to see updates made by others before deciding to integrate them.

Comparison


|Command|What it does|When to use|
|----|-----|---|
|git fetch|Downloads new commits, branches, and tags from the remote but does not merge them into your local branch.|When you want to check for updates without applying them immediately.|
|git pull|Fetches remote changes and automatically merges them into your current branch.|When you want to immediately update your local branch with the latest remote changes.|




Basic Usage of git fetch

    Fetch all remote changes without merging:

git fetch origin

This updates your local copy of remote branches but does not change your working branch.

Fetch a specific branch:

git fetch origin feature/new-feature

This retrieves updates for feature/new-feature but does not switch to it.

Check fetched changes:

git log origin/main --oneline

This shows the latest commits on origin/main after fetching.

Update your branch after fetching:

git merge origin/main

This applies the fetched changes to your local branch manually.

Fetch and switch to a remote branch:

git fetch origin
git checkout -b feature/new-feature origin/feature/new-feature

This creates a local copy of a remote branch and switches to it.

## Reference