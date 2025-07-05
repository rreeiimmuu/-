#include <iostream>

int main() {
    char s1[] = "hello";
    char s2[6]; // 需要足够的空间来存储s1中的字符以及'\\0'
    
    for (int i = 0; s1[i] != '\\0'; i++) {
        s2[i] = s1[i];
    }
    
    s2[5] = '\\0'; // 手动添加'\\0'到s2数组的末尾
    
    // 输出复制后的字符数组s2
    for (int i = 0; s2[i] != '\\0'; i++) {
        std::cout << s2[i];
    }
    std::cout << "\\\\0" << std::endl;
    
    return 0;
}