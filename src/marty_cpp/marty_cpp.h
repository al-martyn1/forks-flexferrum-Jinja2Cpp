/*! \file
    \brief C++ (also good for other langs) identifiers style autodetect and format
 */

#pragma once

#include <string>
#include <cstring>
#include <set>

#include  <cwctype>
#include  <cctype>

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
namespace marty_cpp
{




//----------------------------------------------------------------------------
enum class NameStyle
{
    unknownStyle                   ,
    invalidName                    ,

    cppStyle                       ,
    camelStyle                     ,
    pascalStyle                    ,
    cppCamelMixedStyle             ,
    cppPascalMixedStyle            ,
    defineStyle                    ,
    sqlStyle                         = defineStyle,

    // keep underscores while formatting
    cppUnderscoredStyle            ,
    camelUnderscoredStyle          ,
    pascalUnderscoredStyle         ,
    cppCamelMixedUnderscoredStyle  ,
    cppPascalMixedUnderscoredStyle ,
    defineUnderscoredStyle         , 
    sqlUnderscoredStyle              = defineUnderscoredStyle

};

//------------------------------
struct NameStyleLess
{
    bool operator()( NameStyle n1, NameStyle n2 ) const
    {
        return (int)n1 < (int)n2;
    }
};

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
enum class NameCharClass
{
    unknown      ,
    digit        ,
    lower        ,
    upper        ,
    underscore
};

//------------------------------
inline std::string toString( NameStyle ns )
{
    switch(ns)
    {
        case NameStyle::invalidName         : return "InvalidName";

        case NameStyle::cppStyle            : return "CppStyle";
        case NameStyle::camelStyle          : return "CamelStyle";
        case NameStyle::pascalStyle         : return "PascalStyle";
        case NameStyle::cppCamelMixedStyle  : return "CppCamelMixedStyle";
        case NameStyle::cppPascalMixedStyle : return "CppPascalMixedStyle";
        case NameStyle::defineStyle         : return "DefineStyle";

        case NameStyle::cppUnderscoredStyle            : return "CppUnderscoredStyle";
        case NameStyle::camelUnderscoredStyle          : return "CamelUnderscoredStyle";
        case NameStyle::pascalUnderscoredStyle         : return "PascalUnderscoredStyle";
        case NameStyle::cppCamelMixedUnderscoredStyle  : return "CppCamelMixedUnderscoredStyle";
        case NameStyle::cppPascalMixedUnderscoredStyle : return "CppPascalMixedUnderscoredStyle";
        case NameStyle::defineUnderscoredStyle         : return "DefineUnderscoredStyle";

        default                             : return "UnknownStyle";
    }
}

//------------------------------
inline NameStyle getNameStyleUnderlinedBuddy( NameStyle ns )
{
    switch(ns)
    {
        case NameStyle::cppStyle            : return NameStyle::cppUnderscoredStyle           ;
        case NameStyle::camelStyle          : return NameStyle::camelUnderscoredStyle         ;
        case NameStyle::pascalStyle         : return NameStyle::pascalUnderscoredStyle        ;
        case NameStyle::cppCamelMixedStyle  : return NameStyle::cppCamelMixedUnderscoredStyle ;
        case NameStyle::cppPascalMixedStyle : return NameStyle::cppPascalMixedUnderscoredStyle;
        case NameStyle::defineStyle         : return NameStyle::defineUnderscoredStyle        ;

        default                             : return ns; // return untouched value
    }
}

//------------------------------
inline NameStyle getNameStyleNotUnderlinedBuddy( NameStyle ns )
{
    switch(ns)
    {
        case NameStyle::cppUnderscoredStyle            : return NameStyle::cppStyle           ;
        case NameStyle::camelUnderscoredStyle          : return NameStyle::camelStyle         ;
        case NameStyle::pascalUnderscoredStyle         : return NameStyle::pascalStyle        ;
        case NameStyle::cppCamelMixedUnderscoredStyle  : return NameStyle::cppCamelMixedStyle ;
        case NameStyle::cppPascalMixedUnderscoredStyle : return NameStyle::cppPascalMixedStyle;
        case NameStyle::defineUnderscoredStyle         : return NameStyle::defineStyle        ;

        default                                        : return ns; // return untouched value
    }
}

//------------------------------
inline NameStyle getNameStyleBuddy( NameStyle ns, bool underlinedBuddy )
{
    if (underlinedBuddy)
        return getNameStyleUnderlinedBuddy(ns);
    else
        return getNameStyleNotUnderlinedBuddy(ns);
}

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
// typedef std::set< NameStyle, NameStyleLess, std::allocator<NameStyle> > NameStyleSet;
typedef std::set< NameStyle, NameStyleLess > NameStyleSet;

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
inline NameStyleSet makeAllNameStylesSet()
{
    NameStyleSet allNameStyles;
    allNameStyles.insert( NameStyle::unknownStyle                   );
    allNameStyles.insert( NameStyle::invalidName                    );
    allNameStyles.insert( NameStyle::cppStyle                       );
    allNameStyles.insert( NameStyle::camelStyle                     );
    allNameStyles.insert( NameStyle::pascalStyle                    );
    allNameStyles.insert( NameStyle::cppCamelMixedStyle             );
    allNameStyles.insert( NameStyle::cppPascalMixedStyle            );
    allNameStyles.insert( NameStyle::defineStyle                    );
    allNameStyles.insert( NameStyle::cppUnderscoredStyle            );
    allNameStyles.insert( NameStyle::camelUnderscoredStyle          );
    allNameStyles.insert( NameStyle::pascalUnderscoredStyle         );
    allNameStyles.insert( NameStyle::cppCamelMixedUnderscoredStyle  );
    allNameStyles.insert( NameStyle::cppPascalMixedUnderscoredStyle );
    allNameStyles.insert( NameStyle::defineUnderscoredStyle         );

    return allNameStyles;
}

inline NameStyleSet makeAllNameStyles()
{
    return makeAllNameStylesSet();
}

//----------------------------------------------------------------------------


#if 0

// std::* functions fails on non-ascii chars (assertion failed)

inline bool    isAlpha( char ch )     { return std::isalpha( ch ) ? true : false; }
inline bool    isLower( char ch )     { return std::islower( ch ) ? true : false; }
inline bool    isUpper( char ch )     { return std::isupper( ch ) ? true : false; }
inline bool    isDigit( char ch )     { return std::isdigit( ch ) ? true : false; }
inline bool    getCase( char ch )     { return isUpper(ch); }
inline char    toLower( char ch )     { return (char)std::tolower(ch); }
inline char    toUpper( char ch )     { return (char)std::toupper(ch); }

inline bool    isAlpha( wchar_t ch )  { return std::iswalpha( ch ) ? true : false; }
inline bool    isLower( wchar_t ch )  { return std::iswlower( ch ) ? true : false; }
inline bool    isUpper( wchar_t ch )  { return std::iswupper( ch ) ? true : false; }
inline bool    isDigit( wchar_t ch )  { return std::iswdigit( ch ) ? true : false; }
inline bool    getCase( wchar_t ch )  { return isUpper(ch); }
inline wchar_t toLower( wchar_t ch )  { return (wchar_t)std::towlower(ch); }
inline wchar_t toUpper( wchar_t ch )  { return (wchar_t)std::towupper(ch); }
#endif


//----------------------------------------------------------------------------

inline bool    isLower( char ch )     { return (ch>='a' && ch<='z'); }
inline bool    isUpper( char ch )     { return (ch>='A' && ch<='Z'); }
inline bool    isAlpha( char ch )     { return isLower(ch) || isUpper(ch); }
inline bool    isDigit( char ch )     { return (ch>='0' && ch<='9'); }
inline bool    getCase( char ch )     { return isUpper(ch); }
inline char    toLower( char ch )     { return isUpper(ch) ? ch-'A'+'a' : ch; }
inline char    toUpper( char ch )     { return isLower(ch) ? ch-'a'+'A' : ch; }

inline bool    isLower( wchar_t ch )  { return (ch>=L'a' && ch<=L'z'); }
inline bool    isUpper( wchar_t ch )  { return (ch>=L'A' && ch<=L'Z'); }
inline bool    isAlpha( wchar_t ch )  { return isLower(ch) || isUpper(ch); }
inline bool    isDigit( wchar_t ch )  { return (ch>=L'0' && ch<=L'9'); }
inline bool    getCase( wchar_t ch )  { return isUpper(ch); }
inline wchar_t toLower( wchar_t ch )  { return isUpper(ch) ? ch-L'A'+L'a' : ch; }
inline wchar_t toUpper( wchar_t ch )  { return isLower(ch) ? ch-L'a'+L'A' : ch; }


inline 
bool isValidIdentChar( char ch, bool allowNonAsciiIdents, const std::string &forceAllowedChars )
{
    if (forceAllowedChars.find(ch)!=forceAllowedChars.npos)
        return true; // Force allowed

    if ( (ch>=0 && ch<=' ') || ch==0x7F)
        return false; // space and control chars are invalid

    if (ch>0x7F || ch<0)
    {
        if (allowNonAsciiIdents)
            return true;
        else
            return false;
    }

    // 31 invalid char, 33 ctrl+space, 1 0x7f, and valid - 26 upper alphas, 26 lower alphas, 10 digits, 1 '_' : total 31+33+1+26+26+10+1=128
    static const char* invalidChars = "!\"#$%&\'()*+,-./:;<=>?@[\\]^`{|}~";

    if (std::strchr(invalidChars, ch)!=0)
        return false;

    return true; // Alphanum or '_' char
}

inline 
bool isValidIdentChar( wchar_t ch, bool allowNonAsciiIdents, const std::wstring &forceAllowedChars )
{
    if (forceAllowedChars.find(ch)!=forceAllowedChars.npos)
        return true; // Force allowed

    if ( (ch>=0 && ch<=L' ') || ch==0x7F)
        return false; // space and control chars are invalid

    if (ch>0x7F || ch<0)
    {
        if (allowNonAsciiIdents)
            return true;
        else
            return false;
    }

    // 31 invalid char, 33 ctrl+space, 1 0x7f, and valid - 26 upper alphas, 26 lower alphas, 10 digits, 1 '_' : total 31+33+1+26+26+10+1=128
    static const wchar_t* invalidChars = L"!\"#$%&\'()*+,-./:;<=>?@[\\]^`{|}~";

    if (std::wcschr(invalidChars, ch)!=0)
        return false;

    return true; // Alphanum or '_' char
}

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
template <typename CharT> inline
NameCharClass getNameCharClass( CharT ch, NameCharClass digitCharClass = NameCharClass::digit ) // NameCharClass::lower
{
    if (ch==(CharT)'_')
        return NameCharClass::underscore;

    if (isDigit(ch))
        return digitCharClass;

    if (isLower(ch))
       return NameCharClass::lower;

    if (isUpper(ch))
       return NameCharClass::upper;

    return NameCharClass::unknown;
}


template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline bool isUnderscoreString( const std::basic_string< CharT, Traits, Allocator > &str )
{
    for( auto it = str.begin(); it != str.end(); ++it )
    {
        if (*it!=(CharT)'_')
            return false;
    }

    return true;
}


template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline std::basic_string< CharT, Traits, Allocator >
toLower( const std::basic_string< CharT, Traits, Allocator > &str )
{
    std::basic_string< CharT, Traits, Allocator > resStr;
    for( auto it = str.begin(); it != str.end(); ++it )
    {
        resStr.append( 1, toLower(*it) );
    }

    return resStr;
}

template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline std::basic_string< CharT, Traits, Allocator >
toUpper( const std::basic_string< CharT, Traits, Allocator > &str )
{
    std::basic_string< CharT, Traits, Allocator > resStr;
    for( auto it = str.begin(); it != str.end(); ++it )
    {
        resStr.append( 1, toUpper(*it) );
    }

    return resStr;
}

template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline std::basic_string< CharT, Traits, Allocator >
toPascal( const std::basic_string< CharT, Traits, Allocator > &str )
{
    if (str.empty())
        return str;

    std::basic_string< CharT, Traits, Allocator > resStr = toLower(str);

    std::basic_string< CharT, Traits, Allocator >::iterator it = resStr.begin();
    for(; it!=resStr.end(); ++it)
    {
        auto charClass = getNameCharClass(*it);
        if (charClass==NameCharClass::lower || charClass==NameCharClass::upper)
            break;
    }

    if (it!=resStr.end())
        *it = toUpper(*it);

    return resStr;
}


template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline std::basic_string< CharT, Traits, Allocator >
makeExpandString( const std::basic_string< CharT, Traits, Allocator > &str, std::size_t expandToSize, CharT ch = (CharT)' ' )
{
    if (str.size() >= expandToSize)
        return std::basic_string< CharT, Traits, Allocator >();

    size_t expandStringSize = expandToSize - str.size();

    return std::basic_string< CharT, Traits, Allocator >( expandStringSize, ch );
}


template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline std::basic_string< CharT, Traits, Allocator >
expandAtFront( const std::basic_string< CharT, Traits, Allocator > &str, std::size_t expandToSize, CharT ch = (CharT)' ')
{
    return makeExpandString(str, expandToSize, ch) + str;
}

template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline std::basic_string< CharT, Traits, Allocator >
expandAtBack( const std::basic_string< CharT, Traits, Allocator > &str, std::size_t expandToSize, CharT ch = (CharT)' ')
{
    return str + makeExpandString(str, expandToSize, ch);
}

inline std::string  expandAtFront( const char    * pStr, std::size_t expandToSize, char    ch =  ' ' ) { return expandAtFront( std::string(pStr ), expandToSize, ch ); }
inline std::wstring expandAtFront( const wchar_t * pStr, std::size_t expandToSize, wchar_t ch = L' ' ) { return expandAtFront( std::wstring(pStr), expandToSize, ch ); }

inline std::string  expandAtBack ( const char    * pStr, std::size_t expandToSize, char    ch =  ' ' ) { return expandAtBack ( std::string(pStr ), expandToSize, ch ); }
inline std::wstring expandAtBack ( const wchar_t * pStr, std::size_t expandToSize, wchar_t ch = L' ' ) { return expandAtBack ( std::wstring(pStr), expandToSize, ch ); }


template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline std::basic_string< CharT, Traits, Allocator >
makeString( const char* pStr )
{
    std::basic_string< CharT, Traits, Allocator > resStr;
    for(; *pStr; ++pStr)
    {
        resStr.append( 1, (CharT)*pStr );
    }

    return resStr;
}

template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline std::basic_string< CharT, Traits, Allocator >
trimUnderscoresLeading( const std::basic_string< CharT, Traits, Allocator > &str )
{
    auto beginIt = str.begin();
    for(; beginIt!=str.end() && *beginIt==(CharT)'_'; ++beginIt ) {}

    auto endIt = str.end();

    return std::basic_string< CharT, Traits, Allocator >( beginIt, endIt );
}

template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline std::basic_string< CharT, Traits, Allocator >
trimUnderscoresTrailing( const std::basic_string< CharT, Traits, Allocator > &str )
{
    auto beginIt = str.begin();

    auto endIt = str.end();
    auto endItPrev = endIt;
    if (endItPrev!=str.begin())
       --endItPrev;
    
    for(; endIt!=beginIt && *endItPrev==(CharT)'_'; --endIt, --endItPrev ) { }

    return std::basic_string< CharT, Traits, Allocator >( beginIt, endIt );
}

template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline std::basic_string< CharT, Traits, Allocator >
trimUnderscores( const std::basic_string< CharT, Traits, Allocator > &str )
{
    return trimUnderscoresLeading( trimUnderscoresTrailing(str) );
}


inline std::string  trimUnderscoresLeading ( const char    * pStr ) { return trimUnderscoresLeading( std::string(pStr ) ); }
inline std::wstring trimUnderscoresLeading ( const wchar_t * pStr ) { return trimUnderscoresLeading( std::wstring(pStr) ); }
inline std::string  trimUnderscoresTrailing( const char    * pStr ) { return trimUnderscoresTrailing( std::string(pStr ) ); }
inline std::wstring trimUnderscoresTrailing( const wchar_t * pStr ) { return trimUnderscoresTrailing( std::wstring(pStr) ); }
inline std::string  trimUnderscores        ( const char    * pStr ) { return trimUnderscores( std::string(pStr ) ); }
inline std::wstring trimUnderscores        ( const wchar_t * pStr ) { return trimUnderscores( std::wstring(pStr) ); }



template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
NameStyle detectNameStyleImpl( const std::basic_string< CharT, Traits, Allocator > &str )
{
    bool isValid       = false;
    bool hasFirstUpper = false;
    bool hasLower      = false;
    bool hasUpper      = false;
    bool hasUnderscore = false;
    bool isFirstAlpha  = false;

    std::size_t charCount  = 0;
    std::size_t alphaCount = 0;

    const unsigned FlagHasLower      = 0x01;
    const unsigned FlagHasUpper      = 0x02;
    const unsigned FlagHasUnderscore = 0x04;
    const unsigned FlagFirstUpper    = 0x08;
    //const unsigned FlagFirstUpper    = 0x10;


    for( auto it = str.begin(); it != str.end(); ++it, ++charCount)
    {
        CharT ch = *it;

        if (isAlpha(ch))
        {
            if (!charCount)
            {
                isValid      = true;
                isFirstAlpha = true;
            }

            if (!alphaCount && isUpper(ch))
                hasFirstUpper = true;

            ++alphaCount;

            if (isLower(ch))
                hasLower = true;

            if (isUpper(ch))
                hasUpper = true;

        }

        if (ch==(CharT)'_')
        {
            if (!charCount)
                isValid = true;

            hasUnderscore = true;
        }
    }

    if (!isValid)
        return NameStyle::invalidName;


    unsigned flags = 0;

    if (hasUnderscore)
        flags |= FlagHasUnderscore;

    if (hasLower)
        flags |= FlagHasLower;

    if (hasUpper)
        flags |= FlagHasUpper;

    if (hasFirstUpper)
    {
        flags |= FlagHasUpper;
        flags |= FlagFirstUpper;
    }

    // if (hasFirstUpper)
    //     flags |= FlagFirstUpper;



    switch(flags)
    {
        case FlagHasLower                   :
        case FlagHasLower|FlagHasUnderscore :
             return NameStyle::cppStyle     ;

        case FlagHasUpper                   :
        case FlagHasUpper|FlagFirstUpper    :
        case FlagHasUpper|FlagHasUnderscore :
        case FlagHasUpper|FlagHasUnderscore|FlagFirstUpper :
             return NameStyle::defineStyle  ;

        case FlagHasLower|FlagHasUpper      :
             return NameStyle::camelStyle   ;

        case FlagHasLower|FlagHasUpper|FlagHasUnderscore :
             return NameStyle::cppCamelMixedStyle        ;

        case FlagFirstUpper|FlagHasLower|FlagHasUpper /* |FlagFirstUpper */     :
             return NameStyle::pascalStyle                              ;

        case FlagFirstUpper|FlagHasLower|FlagHasUpper|FlagHasUnderscore /* |FlagFirstUpper */  :
             return NameStyle::cppPascalMixedStyle                                     ;

        default: return NameStyle::unknownStyle;

    }
}

template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
NameStyle detectNameStyle( const std::basic_string< CharT, Traits, Allocator > &str )
{
    if (isUnderscoreString(str))
        return NameStyle::unknownStyle;

    std::basic_string< CharT, Traits, Allocator > ltUnderscoresRemoved = trimUnderscores(str);

    bool hasLeadingOrTrailingUnderscores = false;

    if (ltUnderscoresRemoved!=str)
    {
        hasLeadingOrTrailingUnderscores = true;
    }

    NameStyle baseStyle = detectNameStyleImpl(ltUnderscoresRemoved);

    if (!hasLeadingOrTrailingUnderscores)
        return baseStyle;

    switch(baseStyle)
    {
        case NameStyle::cppStyle           :  return NameStyle::cppUnderscoredStyle           ;
        case NameStyle::camelStyle         :  return NameStyle::camelUnderscoredStyle         ;
        case NameStyle::pascalStyle        :  return NameStyle::pascalUnderscoredStyle        ;
        case NameStyle::cppCamelMixedStyle :  return NameStyle::cppCamelMixedUnderscoredStyle ;
        case NameStyle::cppPascalMixedStyle:  return NameStyle::cppPascalMixedUnderscoredStyle;
        case NameStyle::defineStyle        :  return NameStyle::defineUnderscoredStyle        ;
        default: return baseStyle;
    }

}
 
inline NameStyle detectNameStyle( const char    * pStr )   { return detectNameStyle( std::string(pStr ) ); }
inline NameStyle detectNameStyle( const wchar_t * pStr )   { return detectNameStyle( std::wstring(pStr) ); }



template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline std::vector< std::basic_string< CharT, Traits, Allocator > >
splitName( const std::basic_string< CharT, Traits, Allocator > &str )
{
    std::vector< std::basic_string< CharT, Traits, Allocator > > resVec;
    //std::basic_string< CharT, Traits, Allocator > postfixString;

    auto beginIt = str.begin();

    // Find undercsore prefix
    for(; beginIt!=str.end() && *beginIt==(CharT)'_'; ++beginIt ) {}

    if (beginIt!=str.begin())
    {
        resVec.push_back( std::basic_string< CharT, Traits, Allocator >( str.begin(), beginIt ) );
        // prefixString = std::basic_string< CharT, Traits, Allocator >( str.begin(), it );
    }

    // Find undercsore postfix
    auto endIt = str.end();
    auto endItPrev = endIt;
    if (endItPrev!=str.begin())
       --endItPrev;
    
    for(; endIt!=beginIt && *endItPrev==(CharT)'_'; --endIt, --endItPrev ) { }

    auto postfixBegin = str.end();
    auto postfixEnd   = str.end();

    if (endIt!=str.end())
    {
        // resVec.push_back( std::basic_string< CharT, Traits, Allocator >( endIt, str.end() ) );
        //postfixString = std::basic_string< CharT, Traits, Allocator >( postfixBegin, postfixEnd );
        postfixBegin = endIt;
    }


    NameCharClass prevCharClass = NameCharClass::unknown;
    if (beginIt!=endIt)
    {
        prevCharClass = getNameCharClass( *beginIt, NameCharClass::lower );
    }


    auto startIt = beginIt;
    auto it      = beginIt;

    for( ; it!=endIt; ++it)
    {
        auto curCharClass = getNameCharClass( *it, NameCharClass::lower );
        if (prevCharClass!=curCharClass && !(prevCharClass==NameCharClass::upper && curCharClass==NameCharClass::lower) )
        {
            auto curPartStr = std::basic_string< CharT, Traits, Allocator >(startIt, it);
            startIt = it;
            if (!isUnderscoreString(curPartStr))
            {
                resVec.push_back(curPartStr);
            }
        }

        prevCharClass = curCharClass;
    }

    if (startIt != it)
    {
        auto curPartStr = std::basic_string< CharT, Traits, Allocator >(startIt, it);
        if (!isUnderscoreString(curPartStr))
        {
            resVec.push_back(curPartStr);
        }
    }

    if (postfixBegin!=postfixEnd)
        resVec.push_back(std::basic_string< CharT, Traits, Allocator >( postfixBegin, postfixEnd ));


//  NameCharClass getNameCharClass( CharT ch, NameCharClass digitCharClass = NameCharClass::digit ) // NameCharClass::lower



    /*
    resVec.push_back( makeString<CharT, Traits, Allocator>( "__" ) );
    resVec.push_back( makeString<CharT, Traits, Allocator>( "Youuu" ) );
    resVec.push_back( makeString<CharT, Traits, Allocator>( "Man" ) );
    resVec.push_back( makeString<CharT, Traits, Allocator>( "__" ) );
    */

    return resVec;
}

inline std::vector< std::string  > splitName( const char    * pStr ) { return splitName( std::string(pStr ) ); }
inline std::vector< std::wstring > splitName( const wchar_t * pStr ) { return splitName( std::wstring(pStr) ); }

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline std::basic_string< CharT, Traits, Allocator >
filterName( const std::basic_string< CharT, Traits, Allocator > &str, bool allowNonAsciiIdents, const std::basic_string< CharT, Traits, Allocator > &forceAllowedChars )
{
    typedef std::basic_string< CharT, Traits, Allocator >   string_type;

    string_type res; res.reserve(str.size());

    typename string_type::const_iterator it = str.begin();

    for(; it!=str.end(); ++it)
    {
        if (isValidIdentChar( *it, allowNonAsciiIdents, forceAllowedChars ))
            res.append(1, *it);
        else
            res.append(1, '_');
    }

    return res;

}

//------------------------------
template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline std::basic_string< CharT, Traits, Allocator >
filterName( const std::basic_string< CharT, Traits, Allocator > &str, bool allowNonAsciiIdents )
{
    return filterName(str, allowNonAsciiIdents, std::basic_string< CharT, Traits, Allocator >() );
}

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline std::basic_string< CharT, Traits, Allocator >
fixName( std::basic_string< CharT, Traits, Allocator > str )
{
    if (!str.empty() && isDigit(str[0]))
    {
        str.insert(0, 1, (CharT)'_');
    }

    return str;
    
}

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline std::basic_string< CharT, Traits, Allocator >
formatName( const std::basic_string< CharT, Traits, Allocator > &str, NameStyle nameStyle )
{
    std::vector< std::basic_string< CharT, Traits, Allocator > > nameParts = splitName(str);

    if (nameParts.empty())
        return std::basic_string< CharT, Traits, Allocator >();

    auto beginIt  = nameParts.begin();
    auto endIt    = nameParts.end();

    auto prefixIt = nameParts.end();
    if (isUnderscoreString(*beginIt))
    {
        prefixIt = beginIt;
        ++beginIt;
    }

    auto postfixIt = nameParts.end();
    if (nameParts.size()>1)
    {
        auto tmpIt = postfixIt;
        --tmpIt;
        if (isUnderscoreString(*tmpIt))
        {
            postfixIt = tmpIt;
            endIt     = postfixIt;
        }
    }


    std::basic_string< CharT, Traits, Allocator > strRes;
    bool isFirst = true;
    // make result here

    for(auto it = beginIt; it!=endIt; isFirst = false, ++it )
    {
        if (!strRes.empty())
        {
            if ( nameStyle==NameStyle::cppStyle
              || nameStyle==NameStyle::cppUnderscoredStyle
              || nameStyle==NameStyle::cppCamelMixedStyle
              || nameStyle==NameStyle::cppCamelMixedUnderscoredStyle
              || nameStyle==NameStyle::cppPascalMixedStyle
              || nameStyle==NameStyle::cppPascalMixedUnderscoredStyle
              || nameStyle==NameStyle::defineStyle
              || nameStyle==NameStyle::defineUnderscoredStyle
               )
                strRes.append(1, (CharT)'_');
        }

        switch(nameStyle)
        {
            case NameStyle::cppStyle             :
            case NameStyle::cppUnderscoredStyle  :
                 strRes.append(toLower(*it));
                 break;

            case NameStyle::cppCamelMixedStyle   :
            case NameStyle::camelStyle           :
            case NameStyle::cppCamelMixedUnderscoredStyle:
            case NameStyle::camelUnderscoredStyle:
                 if (isFirst)
                     strRes.append(toLower(*it));
                 else
                     strRes.append(toPascal(*it));
                 break;

            case NameStyle::cppPascalMixedStyle :
            case NameStyle::pascalStyle         :
            case NameStyle::cppPascalMixedUnderscoredStyle:
            case NameStyle::pascalUnderscoredStyle        :
                 strRes.append(toPascal(*it));
                 break;

            case NameStyle::defineStyle           :
            case NameStyle::defineUnderscoredStyle:
                 strRes.append(toUpper(*it));
                 break;

            default                             :
                 strRes.append(*it);

        
        }
    }


    switch(nameStyle)
    {
        //case NameStyle::unknownStyle       :
        //case NameStyle::invalidName        :
        case NameStyle::cppStyle           :
        case NameStyle::camelStyle         :
        case NameStyle::pascalStyle        :
        case NameStyle::cppCamelMixedStyle :
        case NameStyle::cppPascalMixedStyle:
        case NameStyle::defineStyle        :
             return fixName(strRes); // Don't add underscore prefix/suffix
    }

    // add prefix
    if (prefixIt!=nameParts.end())
    {
        strRes = *prefixIt + strRes;
    }

    // add postfix
    if (postfixIt!=nameParts.end())
    {
        strRes = strRes + *postfixIt;
    }

    return fixName(strRes);
}

inline std::string  formatName( const char    * pStr, NameStyle nameStyle ) { return formatName( std::string(pStr ), nameStyle ); }
inline std::wstring formatName( const wchar_t * pStr, NameStyle nameStyle ) { return formatName( std::wstring(pStr), nameStyle ); }
                                   
//----------------------------------------------------------------------------










} // namespace marty_cpp

