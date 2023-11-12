# Modes

1. **Insert mode**: enter `i` to change into
2. **Command mode**: enter `:` to change into
3. **Normal mode**: enter `esc` to change into
4. **Replace mode**: enter `r` to change into (In this mode, it will overwrite the text, instead of inserting text)
5. **Visual mode**: enter `v` to change into, and enter `shift + v` to change into line visual mode, enter `ctrl + v` to change into block visual mode

# Files

1. Enter a certain file in the current directory: `vim fileName.xxx`
2. Open more than one windows: `:sp`
3. Close windows:
	1. Close the current window: `:q`
	2. Force to close the current window: `:q!`
	3. Close all the windows: `:qa`

# Normal mode

1. Move the cursor:
	1. `w`: move to the beginning of the next word
	2. `b`: move to the beginning of the last word
	3. `e`: move to the end of the next word
    4. `0`: move to the beginning of the current line.
    5. `$`: move to the end of the current line.
    6. `^`: move to the first non-empty character.
    7. `hjkl`: move left, down, up, right
    8. `ctrl + u`: scroll up.
    9. `ctrl + d`: scroll down.
    10. `shift + g`: move to the end of the file.
    11. `gg`: move to the beginning of the file.
    12. `ctrl + l`: move to the lowest line on the screen
    13. `ctrl + m`: move to the mid line on the screen
    14. `ctrl + h`: move to the highest line on the screen.
2. Find:
    1. `f + x`: move to the first character x.
    2. `ctrl + f + x`: move to the last character x.
