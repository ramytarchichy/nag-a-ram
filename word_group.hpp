#pragma once

#include <vector>


namespace nagaram
{
    template <class T>
    class word_group
    {
    public:
        word_group(
            const T& sorted,
            const std::vector<T>& words
        ) :
            sorted(sorted),
            words(words)
        {

        }


        inline const T& get_sorted() const noexcept
        {
            return sorted;
        }


        inline const std::vector<T>& get_words() const noexcept
        {
            return words;
        }

    
        std::vector<T> words;//TODO: temporary
    private:
        T sorted;
        //std::vector<T> words; //TODO: replace with pointers?
    };
}
