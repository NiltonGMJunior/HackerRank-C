#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

char* get_substring(char* text, int start, int end) {
    if (text == NULL || start > end || start < 0 || strlen(text) < end) return NULL;
    char* substring = (char*) malloc(sizeof(char) * (end - start + 1));
    strncpy(substring, text + start, end - start);
    strcat(substring, "\0");
    return substring;
}

char** get_sentence(char* text) {
    unsigned int num_spaces = 0;
    for (int i = 0; i < strlen(text); ++i) {
        if (text[i] == ' ') num_spaces++;
    }

    char** sentence = (char**) malloc(sizeof(char*) * (num_spaces + 1));
    for (int i = 0, j = 0, k = 0; i < strlen(text) + 1; ++i) {
        if (text[i] == ' ' || text[i] == '\0') {
            *(sentence + k) = get_substring(text, j, i);
            j = i + 1;
            k++;
        }
    }
    return sentence;
}

char*** get_paragraph(char* text) {
    unsigned int num_periods = 0;
    for (int i = 0; i < strlen(text); ++i) {
        if (text[i] == '.') num_periods++;
    }
    char*** paragraph = (char***) malloc(sizeof(char**) * num_periods);
    for (int i = 0, j = 0, k = 0; i < strlen(text) + 1; ++i) {
        if (text[i] == '.' || text[i] == '\0') {
            *(paragraph + k) = get_sentence(get_substring(text, j, i));
            j = i + 1;
            k++;
        }
    }
    return paragraph;
}

char**** get_document(char* text) {
    unsigned int num_paragraphs = 0;
    for (int i = 0; i < strlen(text); ++i) {
        if (text[i] == '\n') num_paragraphs++;
    }
    char**** document = (char****) malloc(sizeof(char***) * (num_paragraphs + 1));
    for (int i = 0, j = 0, k = 0; i < strlen(text) + 1; ++i)
    {
        if (text[i] == '\n' || text[i] == '\0') {
            *(document + k) = get_paragraph(get_substring(text, j, i));
            j = i + 1;
            k++;
        }
    }
    return document;
}

char* kth_word_in_mth_sentence_of_nth_paragraph(char**** document, int k, int m, int n) {
    return *(*(*(document + n - 1) + m - 1) + k - 1);
}

char** kth_sentence_in_mth_paragraph(char**** document, int k, int m) { 
    return *(*(document + m - 1) + k - 1);
}

char*** kth_paragraph(char**** document, int k) {
    return *(document + k - 1);
}

char* get_input_text() {	
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

void print_word(char* word) {
    printf("%s", word);
}

void print_sentence(char** sentence) {
    int word_count;
    scanf("%d", &word_count);
    for(int i = 0; i < word_count; i++){
        printf("%s", sentence[i]);
        if( i != word_count - 1)
            printf(" ");
    }
} 

void print_paragraph(char*** paragraph) {
    int sentence_count;
    scanf("%d", &sentence_count);
    for (int i = 0; i < sentence_count; i++) {
        print_sentence(*(paragraph + i));
        printf(".");
    }
}

// int main() {
//     char** sentence = get_sentence("Uma frase de teste");
//     print_sentence(sentence);
// }

int main() 
{
    char* text = get_input_text();
    char**** document = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            char* word = kth_word_in_mth_sentence_of_nth_paragraph(document, k, m, n);
            print_word(word);
        }

        else if (type == 2){
            int k, m;
            scanf("%d %d", &k, &m);
            char** sentence = kth_sentence_in_mth_paragraph(document, k, m);
            print_sentence(sentence);
        }

        else{
            int k;
            scanf("%d", &k);
            char*** paragraph = kth_paragraph(document, k);
            print_paragraph(paragraph);
        }
        printf("\n");
    }     
}