1. `strcpy(str1, str2)`：把`str2`复制给`str1`
2. `strcat(str1, str2)`：把`str2`拼接在`str1`末尾
3. `str.size()`：返回`str`的长度
4. `strlen(str)`：返回`str`的长度，从`str`的首位开始，直到遇到`\0`结束，即在str未赋值时返回随机值，但总长度不包括`\0`
5. `getline(cin, str);`：读取`str`
6. `strcmp(str1, str2);`：接受两个字符串地址参数，以系统编码（如ASCII码）比较两个字符串的先后次序，若`str1`应该排在`str2`前，则返回负值；相同则返回0；`str1`应该排在`str2`后，则返回正值 ^92ac06