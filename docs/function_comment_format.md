# C Function Commenting Guide for Hover Documentation

This guide explains how to write C function comments that will appear as helpful tooltips when you hover your mouse cursor over the function name in a code editor or IDE.

This relies on a convention called **Doxygen-style comments**, which many editors recognize.

## 1. The Basic Structure

Use a special comment block that starts with `/**` (note the two asterisks) and ends with `*/`. Place this comment block *immediately* before the function declaration or definition.

```c
/**
 * This is a brief description of the function.
 * 
 * This is a more detailed description, which can
 * span multiple lines.
 */
int my_function(int arg1, const char *arg2);
```

## 2. Key Doxygen Tags

Doxygen tags start with \ or @. Here are the most important ones for function documentation:

- \brief (or @brief): A short, one-sentence summary of the function's purpose. This is often what's displayed in the first line of the hover tooltip. This is optional if the first sentence of your comment is already a good summary.

- \param (or @param): Describes a function parameter. Include the parameter name and a description. Use one \param tag for each parameter.

- \return (or @return): Describes the return value of the function. Explain what the function returns, including any special values (e.g., error codes).

- \retval (or @retval) This is for describing specific return values and their meanings (e.g. error codes). It's especially useful if you return different integer codes to indicate success or different types of failure.

- \note (or @note) Important notes, considerations, or caveats about using the function.

- \warning (or @warning) Used for warnings, possible problems, or situations where special care must be taken.

- \pre (or @pre): Describes preconditions. Things that MUST be true before calling the function.

- \post (or @post): Describes postconditions. Things that will be true after the function executes successfully.

## 3. Complete Example

```c
/**
 * @brief Calculates the sum of two integers.
 *
 * This function takes two integer arguments and returns their sum.
 * It handles integer overflow by returning INT_MAX if the sum
 * exceeds the maximum representable value, and INT_MIN if the
 * sum is less than the minimum representable value.
 *
 * @param a The first integer.
 * @param b The second integer.
 *
 * @return The sum of a and b, or INT_MAX/INT_MIN on overflow.
 *
 * @retval INT_MAX  If the sum overflows (positive).
 * @retval INT_MIN  If the sum overflows (negative).
 *
 * @note This function does not check for NULL pointers (as it takes integers).
 *
 * @warning Be mindful of potential integer overflow.
 *
 * @pre a and b must be valid integers.
 * @post The result is the sum of a and b, or an overflow indicator.
 */
int add(int a, int b) {
    long long sum = (long long)a + (long long)b;
    if (sum > INT_MAX) {
        return INT_MAX;
    }
    if (sum < INT_MIN) {
        return INT_MIN;
    }
    return (int)sum;
}
```

## 4. Parameter Direction ([in], [out], [in,out])

For clarity, especially with pointers, you can indicate the direction of data flow for parameters:

- [in]: The parameter is an input to the function. The function reads from this parameter but does not modify it (from the caller's perspective).

- [out]: The parameter is an output from the function. The function writes to this parameter. The initial value of the parameter (from the caller's perspective) is typically irrelevant.

- [in,out]: The parameter is both an input and an output. The function reads the initial value and may modify it.

```c
/**
 * @brief Copies a string, allocating memory for the copy.
 *
 * @param[in] src  The source string to copy.  Must be null-terminated.
 * @param[out] dest A pointer to a pointer that will hold the address of the
 *                  newly allocated string.  The caller is responsible for
 *                  freeing this memory.
 *
 * @return 0 on success, -1 on allocation failure.
 *
 * @pre src must be a valid, null-terminated string.
 * @post If successful, *dest will point to a newly allocated string.
 *       If unsuccessful, *dest will be unchanged.
 */
int string_copy(const char *src, char **dest) {
    if (src == NULL) {
        return -1; // Or handle the error as appropriate
    }

    size_t len = strlen(src);
    *dest = (char *)malloc(len + 1);
    if (*dest == NULL) {
        return -1; // Allocation failed
    }

    strcpy(*dest, src);
    return 0;
}
```

5. Key Considerations
Consistency: Be consistent in your commenting style throughout your project.

Clarity: Write clear, concise, and unambiguous descriptions. Avoid jargon.

Completeness: Document all public functions, parameters, and return values.

Accuracy: Keep your comments up-to-date with your code. Outdated comments are worse than no comments.

IDE Support: Most modern C IDEs (including VS Code with the C/C++ extension, CLion, and many others) will automatically parse these Doxygen-style comments and display them in tooltips, autocomplete suggestions, and generated documentation.

Doxygen Tool: While you don't need to run the Doxygen tool itself to get hover documentation, Doxygen can generate complete HTML documentation from your code if you use this commenting style. This can be extremely useful for larger projects.