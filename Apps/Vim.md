# Modes

1. **Insert mode**: enter `i` to change into
2. **Command mode**: enter `:` to change into
3. **Normal mode**: enter `esc` to change into
4. **Replace mode**: enter `r` to change into (In this mode, it will overwrite the text, instead of inserting text)
5. **Visual mode**: enter `v` to change into, and enter `shift + v` to change into line visual mode, enter `ctrl + v` to change into block visual mode

# Command mode

1. Enter a certain file in the current directory(in command line): `vim fileName.xxx`
2. Open more than one windows: `:sp`
3. Close windows:
	1. Close the current window: `:q`
	2. Force to close the current window: `:q!`
	3. Close all the windows: `:qa`
4. Search: use `/ + <ThingsToSearch>` to jump to where the string in the `<>` first appears. And enter `n` after that to get to the next place.
	1. after use the command above, use command `n` to get to the next place, and `shift + n` to get to the last place.
5. Close the search highlight: `: + noh`
6. Split the screen:
	1. `: + sp`: 上下分屏
	2. `: + vsp`：左右分屏
	3. `q`: quit the split
	4. Move between the windows: `ctrl + w`, then use `h j k l` to move around
7. Change color: `: + color + <colorName>`
8. Tab:
	1. Open a new tab: `:tabe`
	2. Move to the left tab: `:-tabnext`
	3. Move to the right tab: `:+tabnext`
9. Open other files:
	1. `:e + <file>`, using tab to release your burden.

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
    13. `ctrl + m`: move to the midline on the screen
    14. `ctrl + h`: move to the highest line on the screen.
    15. `{`: move to the first blank line above
    16. `}`: move to the first blank line below
    17. `A`：move to the end of the line and change into insert mode
2. Find:
    1. `f + x`: move to the first  afterward character x.
    2. `shift + f + x`: move to the first forward character x.
    3. `t + x`: move to the letter just right before `x`
    4. `shift + t + x`: move to the letter just after `x`
    5. `<command> + f + x`: do the command from the current place to the first x after that.
3. Delete: use `d` key
	1. `d + d`: delete the whole line
	2. `d + w`: delete the word where your cursor is from the cursor to the first character of the next word
	3. `d + e`: delete the word where your cursor is from the cursor the the end of the word
	4. `d + d`: delete the whole line
	5. `d + 0`: delete from the cursor to the beginning of the line.
	6. `d + $`: delete from the cursor to the end of the line.
	7. `x`: delete the letter where your cursor is.
	8. `s`: equals to `x + i`(delete the current letter and enter the insert mode)
4. Change: 
	1. use `c` key to delete and enter the insert mode, just like the `d` key.
	2. use `r + x`  to replace the letter where your cursor is with `x`
5. Undo:
	1. `u`: to undo the last step
	2. `ctrl + r`: redo the last undo
6. Copy: use `y` key, act like `d` and `c`
	1. `y + i + (`: yank inside the parentheses
	2. `y + f + x`: yank from the current place to the first character x after the cursor
7. Paste: use `p` key to paste what you have copied
8. Counts: enter a number before other commands to operate the command for a certain time, like `3 + d + d` will delete 3 whole lines at a time
9. Modifier commands: 
	1. `i`: when inside the parentheses or square brackets, using `x + i + y` means use the command `x` inside the parentheses or square brackets.(like `c + i + [` means using `c` inside the square brackets, and `c + i + w` means change inside the word)
	2. 
10. Repeat: after using a certain command, move to another place and then press key `.` to repeat the same command.
11. 分屏：分屏后使用`:e <file-path>`来打开相应文件

# Insert mode

1. Enter the insert mode:
	1. `i`: begin your coding right before the cursor
	2. `a`: begin your coding right after the cursor
	3. `o`: create and jump to a new line right down the cursor
	4. `shift + o`: create and jump to a new line right above the cursor
	5. `shift + i`: insert at the beginning of the cursor line
	6. `shift + a`: append at the end of the cursor line

# Visual mode

1. Enter the visual mode with `v` key.
2. You can move your cursor with most of the commands in the normal mode, the only difference is that the block between the beginning of your cursor and the current place will be selected, and now you can use the **copy** commands. It will copy the text block selected and enter the normal mode.
3. There is also a visual line mode, which you can enter by pressing `shift + v`. In this visual mode, you will select the whole lines at a time.
4. There is also a visual block mode, which you can enter by pressing `ctrl + v`. In this visual mode, you will select the whole lines at a time.
5. Some commands:
	1. `~`: after selecting a block, press `~` key to flip the whole block. You can also just press `~` without selecting, and it will only change the letter where the cursor is.
	2. `: + normal + <normal-mode-commands>`: select lines of text and use this command can do the command repeatedly in every line.
6. Enter `:` in visual mode, choose some lines, then enter `normal` and some commands, the vim editor will do the commands at each of the lines.