#include <algorithm>
#include <string>
#include <string_view>
#include <iostream>
#include <cctype>

using namespace std;


template< class ForwardIt, class T >
ForwardIt remove(ForwardIt first, ForwardIt last, const T& value)
{
    first = std::find(first, last, value);
    if (first != last)
        for(ForwardIt i = first; ++i != last; )
            if (!(*i == value))
                *first++ = std::move(*i);
    return first;
}

template<class ForwardIt, class UnaryPredicate>
ForwardIt remove_if_el(ForwardIt first, ForwardIt last, UnaryPredicate p)
{
    first = std::find_if(first, last, p);
    if (first != last)
        for(ForwardIt i = first; ++i != last; )
            if (!p(*i))
                *first++ = std::move(*i);
    return first;
}


int main()
{
    std::string str1 = "Text with some   spaces";
    
 
    auto noSpaceEnd = std::remove(str1.begin(), str1.end(), ' ');
 
    // The spaces are removed from the string only logically.
    // Note, we use view, the original string is still not shrunk:
    // std::cout << std::string_view(str1.begin(), noSpaceEnd) << " size: " << str1.size() << '\n';
    std::cout << str1 << " size: " << str1.size() << '\n';
 
    str1.erase(noSpaceEnd, str1.end());
 
    // The spaces are removed from the string physically.
    std::cout << str1 << " size: " << str1.size() << '\n';
 
    std::string str2 = "Text\n with\tsome \t  whitespaces\n\n";
    str2.erase(remove_if(str2.begin(), 
                              str2.end(),
                              [](unsigned char x){return std::isspace(x);}),
               str2.end());
    std::cout << str2 << '\n';

    return 0;
}