//@AUTHOR : Guilherme Cardoso Oliveira <guilherme.cardoso-oliveira@unesp.br>
//@lICENSE: MIT
//@DATE   : 2024-09-03

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#define DATA_STRUCT_NAME "String"

//-----------------------------------------------------------
//DATA

typedef char * String;
#define DATA_FORMAT "%s"

//-----------------------------------------------------------
//STRING METHODS

// Checks if a string is NULL
bool strnull(String src) {
     return src == NULL;
}

// Assert String
bool strassert(String src) {
     if(strnull(src)) {
		printf("[ERR] ");
		printf(DATA_STRUCT_NAME);
		printf(" isn't initialized!");
		exit(EXIT_FAILURE);
	}
}

// Checks if a string is empty
bool strempty(String src) {
     strassert(src);
     
     unsigned int i = 0;
     while(src[i] != '\0') {
         if(src[i] != ' ')
             return false;
         
         i++;    
     }
     
     return true;
}

// Creates a new string
String newString(unsigned int maxlength) {
	String string  = (String) malloc(sizeof(char) * (maxlength + 1));
	
	if(strnull(string)) {
		printf("[ERR] Not enough memory");
		exit(EXIT_FAILURE);
	}
	
	return string;
}

// Gets the string length
unsigned int strlength(String src) {
    unsigned int i = 0;
    while(src[i] != '\0') i++;
    return i;
}

// Print the string
void strprint(String src) {
	printf("%s\n", src);
}

// Verify if two strings are equals
bool strequal(String str1, String str2) {
    strassert(str1);
    strassert(str2);
    
    unsigned int length1 = strlength(str1);
    unsigned int length2 = strlength(str2);
    if(length1 != length2) return false;
    
    unsigned int i = 0;
    while(i <= length1) {
        if(str1[i] != str2[i])
            return false;
            
        i++;
    }
    
    return true;
}

// Gets a string copy
String strcopy(String src) {
    unsigned int length = strlength(src);
    String copied =  newString(length);
    
    unsigned int i = 0;
    do {
       copied[i] = src[i];
    } while(src[i++] != '\0');
    
    return copied;
}

// Concatenates two strings
String strconcat(String str1, String str2) {
    strassert(str1);
    strassert(str2);
    
    unsigned int length1 = strlength(str1);
    unsigned int length2 = strlength(str2);
    String concatenated = newString(length1 + length2);
    
    unsigned int i = 0;
    for(; i < length1; i++)
        concatenated[i] = str1[i];
    
    for(unsigned int j = 0; j < length2; j++, i++)
        concatenated[i] = str2[j];
    
    concatenated[length1 + length2] = '\0';
    return concatenated;
}

// Reverses the string
String strreverse(String src) {
    strassert(src);
    unsigned int length = strlength(src);
    String reversed = newString(length);
    
    for(unsigned int i = 0; i < length; i++)
        reversed[i] = src[length - i - 1];

    reversed[length] = '\0';
    return reversed;
}

// Converts all characters of the string to uppercase
String strupper(String src) {
    strassert(src);
    unsigned int length = strlength(src);
    String upper = newString(length);
    
    for (unsigned int i = 0; i < length; i++)
        upper[i] = toupper(src[i]);
    
    upper[length] = '\0';
    return upper;
}

// Converts all characters of the string to lowercase
String strlower(String src) {
    strassert(src);
    unsigned int length = strlength(src);
    String lower = newString(length);
    
    for (unsigned int i = 0; i < length; i++)
        lower[i] = tolower(src[i]);

    lower[length] = '\0';
    return lower;
}

// Checks if 'substr' is a substring of 'str'
bool strcontains(String str, String substr) {
    strassert(str);
    strassert(substr);

    unsigned int strLength = strlength(str);
    unsigned int substrLength = strlength(substr);

    if (substrLength == 0 || strLength < substrLength)
        return false;

    for (unsigned int i = 0; i <= strLength - substrLength; i++) {
        unsigned int j = 0;
        while (j < substrLength && str[i + j] == substr[j]) {
            j++;
        }
        
        if (j == substrLength) {
            return true;
        }
    }

    return false;
}

// Finds the first occurrence of a character in a string
int strcharpos(String src, char c) {
    strassert(src);
    unsigned int length = strlength(src);
    
    for (unsigned int i = 0; i < length; i++) {
        if (src[i] == c) {
            return i;
        }
    }
    
    return -1; // Character not found
}

// Verify if a string is a palindrome
bool strpalindrome(String src) {
    unsigned int length = strlength(src);
    unsigned int i=0, j=length-1;
    
    while(i <= j)
        if(src[i++] != src[j--])
            return false;

    return true;
}



//-----------------------------------------------------------
//MAIN

int main() {
    // Example 1: Copy and print a string
    String copy = strcopy("Hello, World!");
    strprint(copy); // Output: Hello, World!


    // Example 2: Concatenate two strings
    String str1 = strcopy("Hello");
    String str2 = strcopy(", World!");
    String concatenated = strconcat(str1, str2);
    strprint(concatenated); // Output: Hello, World!

    // Example 3: Reverse a string
    String reversed = strreverse(concatenated);
    strprint(reversed); // Output: !dlroW ,olleH


    // Example 4: Convert a string to uppercase
    String upper = strupper(copy);
    strprint(upper); // Output: HELLO, WORLD!


    // Example 5: Convert a string to lowercase
    String lower = strlower(copy);
    strprint(lower); // Output: hello, world!


    // Example 6: Check if a string contains another string
    bool contains = strcontains(copy, "World");
    printf("Contains 'World': %s\n", contains ? "true" : "false"); // Output: true


    // Example 7: Find the position of a character
    int pos = strcharpos(copy, 'W');
    if (pos != -1) {
        printf("Character 'W' found at position: %d\n", pos); // Output: Character 'W' found at position: 7
    } else {
        printf("Character 'W' not found\n");
    }


    // Example 8: Check if a string is a palindrome
    String palindromeStr = strcopy("madam");
    bool isPalindrome = strpalindrome(palindromeStr);
    printf("Is palindrome: %s\n", isPalindrome ? "true" : "false"); // Output: true


    // Free the allocated memory
    free(copy);
    free(concatenated);
    free(reversed);
    free(upper);
    free(lower);
    free(str1);
    free(str2);
    free(palindromeStr);

    system("pause");
    return 0;
}
