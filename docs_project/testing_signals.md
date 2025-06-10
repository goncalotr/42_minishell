# Minishell Signal Handling

### Test Case 1: Interactive Prompt Behavior

`Ctrl+C` (SIGINT) at an empty prompt

`Ctrl+C` with text in the buffer

`Ctrl+\` (SIGQUIT) at the prompt

`Ctrl+D` (EOF) at an empty prompt

### Test Case 2: During Child Process Execution

`Ctrl+C` during a running command

`Ctrl+\` during a running command

### Test Case 3: During Heredoc Input

`Ctrl+C` during a heredoc
