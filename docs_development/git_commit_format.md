# Git Commit Message Format

This guide outlines the Conventional Commits specification, a widely adopted standard for writing clear and consistent Git commit messages.

## 1 Intro

Each -m flag adds a new paragraph to the commit message.

``` sh
git commit -m "type(scope): subject" -m "Body of the commit message." -m "Footer information if necessary."
```

```sh
git commit -m "docs(comments): add function comments documentation" \
            -m "Provide detailed documentation comments for all public functions. 
            This improves code readability and helps new contributors understand the codebase."
```

## 2 Commit Message Format

Each commit message consists of a header, a body and a footer. The header has a special format that includes a type, a scope and a subject:

```
<type>[optional scope]: <description>

[optional body]

[optional footer(s)]
```
**The header is mandatory and the scope of the header is optional.**

**Any line of the commit message cannot be longer 100 characters!** This allows the message to be easier to read on GitHub as well as in various git tools.

## 3 Comment Parts

### Types

Must be one of the following:

- feat: A new feature
- fix: A bug fix
- docs: Documentation only changes
- style: Changes that do not affect the meaning of the code (white-space, formatting, missing semi-colons, etc)
- refactor: A code change that neither fixes a bug nor adds a feature
- perf: A code change that improves performance
- test: Adding missing tests
- chore: Changes to the build process or auxiliary tools and libraries such as documentation generation

### Scope

The scope could be anything specifying place of the commit change. For example `$location`, `$browser`, `$compile`, `$rootScope`, `ngHref`, `ngClick`, `ngView`, etc…

### Subject

The subject contains succinct description of the change:
- **use the imperative, present tense: “change” not “changed” nor “changes”**
- **don’t capitalize first letter**
- **no dot (.) at the end**

### Body

Just as in the subject, use the imperative, present tense: “change” not “changed” nor “changes”. The body should include the motivation for the change and contrast this with previous behavior.

### Footer

The footer should contain any information about Breaking Changes and is also the place to reference GitHub issues that this commit Closes.

Breaking Changes should start with the word BREAKING CHANGE: with a space or two newlines. The rest of the commit message is then used for this.

## 4 Usage

### 4.1 Revert

If the commit reverts a previous commit, it should begin with revert:, followed by the header of the reverted commit. In the body it should say: `This reverts commit <hash>.`, where the hash is the SHA of the commit being reverted.

## 5 Examples

### Features

```sh
feat(parser): improve parsing performance for large datasets

Optimize the parsing algorithm to handle large files more efficiently.  
The new approach reduces memory usage and improves processing speed by 20%.
```


### Documentation

```sh
docs(README): update subject description
```

```sh
docs(user-manual): add user manual for setup and usage

Introduce a user manual covering installation, configuration, and common troubleshooting steps.  
This aims to help users set up the system quickly and resolve minor issues independently.
```





## 5 Reference

- https://ec.europa.eu/component-library/v1.15.0/eu/docs/conventions/git/
- https://www.conventionalcommits.org/en/v1.0.0/
