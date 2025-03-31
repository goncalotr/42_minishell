# GitHub Markdown Guide

This guide covers the basics of Markdown as used on GitHub. It focuses only on features supported by GitHub Flavored Markdown (GFM).

## 1. Headings

Use `#` symbols to create headings.  The number of `#` symbols corresponds to the heading level (H1 to H6).

```markdown
# H1 Heading
## H2 Heading
### H3 Heading
#### H4 Heading
##### H5 Heading
###### H6 Heading
```
Renders as:
# H1 Heading
## H2 Heading
### H3 Heading
#### H4 Heading
##### H5 Heading
###### H6 Heading

## 2. Text Formatting

Bold: Wrap text with double asterisks (**) or double underscores (__).

```markdown
**This is bold text.**  __This is also bold text.__
```

**This is bold text.**  __This is also bold text.__

Italic: Wrap text with single asterisks (*) or single underscores (_).


```markdown
*This is italic text.* _This is also italic text._
```

*This is italic text.* _This is also italic text._

Bold and Italic: Combine asterisks or underscores.

```markdown
***This is bold and italic.***  ___This is also bold and italic.___
```

***This is bold and italic.***  ___This is also bold and italic.___

Strikethrough: Wrap text with double tildes (~~).

```markdown
~~This text is struck through.~~
```

~~This text is struck through.~~

## 3. Lists

Unordered Lists: Use asterisks (*), plus signs (+), or hyphens (-) as bullet points. Indent for sub-lists.

```markdown
* Item 1
* Item 2
  * Subitem 2.1
  * Subitem 2.2
* Item 3
```
* Item 1
* Item 2
  * Subitem 2.1
  * Subitem 2.2
* Item 3

Ordered Lists: Use numbers followed by periods. GitHub automatically renumbers the list if you don't use sequential numbers.

```markdown
1. First item
2. Second item
5. Third item (GitHub will display this as "3.")
   1. Sub item
   2. Sub item 2
```

1. First item
2. Second item
5. Third item (GitHub will display this as "3.")
   1. Sub item
   2. Sub item 2

## 4. Links

Inline Links: [Link text](URL "Optional Title")

```markdown
This is a link to [Google](https://www.google.com "Google's Homepage").
```

This is a link to [Google](https://www.google.com "Google's Homepage").

Relative Links: You can link to files within your repository.

```markdown
See the [README](./README.md) for more information.
```

See the [README](./README.md) for more information.

Automatic Linking: GitHub will automatically create a link if you paste a raw URL:

```markdown
https://www.example.com
```

https://www.example.com

## 5. Images

Inline Images: ![Alt text](Image URL "Optional Title")

```markdown
![GitHub Logo](https://github.githubassets.com/images/modules/logos_page/GitHub-Mark.png "GitHub Logo")
```

![GitHub Logo](https://github.githubassets.com/images/modules/logos_page/GitHub-Mark.png "GitHub Logo")

Alt text is important for accessibility and is displayed if the image fails to load.
Image URL can be a URL or a relative path to an image in your repository.

## 6. Code

Inline Code: Wrap code with single backticks (`).

```markdown
Use the `git status` command to check the status of your repository.
```

Use the `git status` command to check the status of your repository.

Code Blocks: Use triple backticks (```) to create a code block. You can specify the language for syntax highlighting.

```markdown
	```python
	def my_function(x):
	    return x * 2

	print(my_function(5))
	```
```

```python
def my_function(x):
    return x * 2

print(my_function(5))
```
Some common language identifiers: python, javascript, html, css, java, cpp, go, ruby, bash, json, sql, markdown, xml. GitHub supports many more.

## 7. Blockquotes

Use the > symbol at the beginning of a line to create a blockquote.

```markdown
> This is a blockquote.
> It can span multiple lines.
>
> > Nested blockquotes are also possible.
```

> This is a blockquote.
> It can span multiple lines.
>
> > Nested blockquotes are also possible.

## 8. Horizontal Rules

Use three or more hyphens (---), asterisks (***), or underscores (___) on a line by themselves to create a horizontal rule.

```markdown
---
***
___
```

---
***
___

## 9. Tables

Use pipes (|) and hyphens (-) to create tables. The hyphens separate the header row from the table body. Colons (:) can be used to align columns.

```markdown
| Header 1 | Header 2 | Header 3 |
| :------- | :------: | -------: |
| Left     | Center   | Right    |
| Row 2    |  Cell   |  Data    |
```

| Header 1 | Header 2 | Header 3 |
| :------- | :------: | -------: |
| Left     | Center   | Right    |
| Row 2    |  Cell   |  Data    |

Options:
- :--- (left-aligned)
- :---: (center-aligned)
- ---: (right-aligned)

## 10. Task Lists

Create interactive checklists using - [ ] for unchecked items and - [x] for checked items.

```markdown
- [x] Complete task 1
- [ ] Task 2
- [ ] Task 3
```

- [x] Complete task 1
- [ ] Task 2
- [ ] Task 3

## 11. Emojis

GitHub supports a wide range of emojis. Use the colon syntax :emoji_name:.

```markdown
:smile: :rocket: :tada:
```

:smile: :rocket: :tada:

## 12. @mentions and #issues

@mentions: Mention users by typing @ followed by their GitHub username. This will notify them.

```markdown
Thanks for the help, @user_name!
```

#issues and #pull requests: Reference issues and pull requests by typing # followed by the issue/PR number.

```markdown
This fixes #123.  See also #456.
```

GitHub will automatically link these to the corresponding issue or pull request.


## 13. Ignoring Markdown formatting

You can escape Markdown characters using a backslash (\).

```markdown
\*This text will not be italic.\*
```

\*This text will not be italic.\*

## 14. Comments

We can add comments to markdown documents with the following notation:

```sh
<!---
your comment goes here
and here
-->
```

Between this and the following line we have that comment snippet present again, but you aren't able to see it in the document.

<!---
your comment goes here
and here
-->

Before this line we have a HTML tag. The advantage is that it works with pandoc when generating TeX or HTML output.

Reference:
https://stackoverflow.com/questions/4823468/comments-in-markdown

