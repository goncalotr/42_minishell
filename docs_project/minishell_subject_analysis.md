# Analysis of project goals and requirements

Minishell stages:

- Input: Get the command line string from the user.
- Lexical Analysis (Tokenization): Break the input string into a sequence of tokens.
- Parsing: Analyze the tokens and build an Abstract Syntax Tree (AST).
- Expansion: Handle variable expansion, quote removal, and tilde expansion.
- Execution: Execute the commands represented by the AST.
- Cleanup: Free allocated memory and prepare for the next input.

