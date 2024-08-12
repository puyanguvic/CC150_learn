#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100
#define MAX_WORDS 10000

struct WordCount {
    char word[MAX_WORD_LENGTH];
    int count;
};

struct WordFrequencyCounter {
    struct WordCount wordCounts[MAX_WORDS];
    int uniqueWords;
};

void toLowerCase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void removePunctuation(char* str) {
    int i, j;
    for (i = j = 0; str[i]; i++) {
        if (!ispunct(str[i])) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

void initWordFrequencyCounter(struct WordFrequencyCounter* counter) {
    counter->uniqueWords = 0;
}

void processText(struct WordFrequencyCounter* counter, const char* text) {
    char word[MAX_WORD_LENGTH];
    int wordIndex = 0;

    for (int i = 0; text[i]; i++) {
        if (isspace(text[i])) {
            if (wordIndex > 0) {
                word[wordIndex] = '\0';
                toLowerCase(word);
                removePunctuation(word);

                if (word[0] != '\0') {
                    int found = 0;
                    for (int j = 0; j < counter->uniqueWords; j++) {
                        if (strcmp(counter->wordCounts[j].word, word) == 0) {
                            counter->wordCounts[j].count++;
                            found = 1;
                            break;
                        }
                    }
                    if (!found && counter->uniqueWords < MAX_WORDS) {
                        strcpy(counter->wordCounts[counter->uniqueWords].word, word);
                        counter->wordCounts[counter->uniqueWords].count = 1;
                        counter->uniqueWords++;
                    }
                }
                wordIndex = 0;
            }
        } else {
            if (wordIndex < MAX_WORD_LENGTH - 1) {
                word[wordIndex++] = text[i];
            }
        }
    }

    // Process the last word if exists
    if (wordIndex > 0) {
        word[wordIndex] = '\0';
        toLowerCase(word);
        removePunctuation(word);

        if (word[0] != '\0') {
            int found = 0;
            for (int j = 0; j < counter->uniqueWords; j++) {
                if (strcmp(counter->wordCounts[j].word, word) == 0) {
                    counter->wordCounts[j].count++;
                    found = 1;
                    break;
                }
            }
            if (!found && counter->uniqueWords < MAX_WORDS) {
                strcpy(counter->wordCounts[counter->uniqueWords].word, word);
                counter->wordCounts[counter->uniqueWords].count = 1;
                counter->uniqueWords++;
            }
        }
    }
}

int getWordFrequency(const struct WordFrequencyCounter* counter, const char* word) {
    char lowercaseWord[MAX_WORD_LENGTH];
    strncpy(lowercaseWord, word, MAX_WORD_LENGTH - 1);
    lowercaseWord[MAX_WORD_LENGTH - 1] = '\0';
    toLowerCase(lowercaseWord);
    removePunctuation(lowercaseWord);

    for (int i = 0; i < counter->uniqueWords; i++) {
        if (strcmp(counter->wordCounts[i].word, lowercaseWord) == 0) {
            return counter->wordCounts[i].count;
        }
    }
    return 0;
}

void resetCounter(struct WordFrequencyCounter* counter) {
    counter->uniqueWords = 0;
}

int main() {
    struct WordFrequencyCounter counter;
    initWordFrequencyCounter(&counter);

    const char* book_content = "This is a sample text. This text is used to demonstrate word frequency counting. The word 'is' appears multiple times in this text.";
    
    processText(&counter, book_content);

    printf("Frequency of 'is': %d\n", getWordFrequency(&counter, "is"));
    printf("Frequency of 'text': %d\n", getWordFrequency(&counter, "text"));
    printf("Frequency of 'sample': %d\n", getWordFrequency(&counter, "sample"));

    // Reset and process new text
    resetCounter(&counter);
    processText(&counter, "New text to process. This is a different text.");

    printf("Frequency of 'text' in new content: %d\n", getWordFrequency(&counter, "text"));

    return 0;
}