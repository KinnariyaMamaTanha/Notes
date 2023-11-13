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
    1. `f + x`: move to the first  afterward character x.
    2. `shift + f + x`: move to the first forward character x.
    3. `t + x`: move to the letter just right before `x`
    4. `shift + t + x`: move to the letter just after `x`
3. Delete: use `d` key
	1. `d + d`: delete the whole line
	2. `d + w`: delete the word where your cursor is from the cursor to the first character of the next word
	3. `d + e`: delete the word where your cursor is from the cursor the the end of the word
	4. `d + d`: delete the whole line
	5. `d + 0`: delete from the cursor to the beginning of the line.
	6. `d + $`: delete from the cursor to the end of the line.
	7. `x`: delete the letter where your cursor is.
4. Change: 
	1. use `c` key to delete and enter the insert mode, just like the `d` key.
	2. use `r + x`  to replace the letter where your cursor is with `x`
5. Undo:
	1. `u`: to undo the last step
6. Copy: use `y` key, act like `d` and `c`
7. Paste: use `p` key to paste what you have copied
8. Counts: enter a number before other commands to operate the command for a certain time, like `3 + d + d` will delete 3 whole lines at a time

# Insert mode

1. Enter the insert mode:
	1. `i`: begin your coding right before the cursor
	2. `a`: begin your coding right after the cursor
	3. `o`: create and jump to a new line right down the cursor
	4. `shift + o`: create and jump to a new line right above the cursor

# Visual mode

1. Enter the visual mode with `v` key.
2. You can move your cursor with most of the commands in the normal mode, the only difference is that the block between the beginning of your cursor and the current place will be selected, and now you can use the **copy** commands. It will copy the text block selected and enter the normal mode.
3. There is also a visual line mode, which you can enter by pressing `shift + v`. In this visual mode, you will select the whole lines at a time.
4. Some commands:
	1. `~`: after selecting a block, press `~` key to flip the whole block. You can also just press `~` without selecting, and it will only change the letter where the cursor is.