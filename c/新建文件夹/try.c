bool isValid(char *word)
{
    int len = strlen(word);
    if (len < 3)
    {
        return false;
    }
    bool v = false;
    bool has_consonant = false;
    for (int i = 0; i < len; i++)
    {
        char c = word[i];
        if (isalpha(c))
        {
            c = tolower(c);
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
            {
                v = true;
            }
            else
            {
                has_consonant = true;
            }
        }
        else if (!isdigit(c))
        {
            return false;
        }
    }
    return v && has_consonant;
}