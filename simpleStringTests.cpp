#include <cstring> // strlen()

#include <iostream>
#include <sstream> // std::ostringstream
#include <gtest/gtest.h>

#if __has_include("../simpleString.h")
    #include "../simpleString.h"
#elif __has_include("simpleString.h")
    #include "simpleString.h"
#else
    #error "File 'simpleString.h' not found!"
#endif

using namespace std;
using namespace ::testing;


namespace
{
    size_t allocations{};
    size_t deallocations{};
} // namespace

void* operator new[](size_t N)
{
    ++allocations;
    return malloc(N);
}
void operator delete[](void* memory) noexcept
{
    ++deallocations;
    return free(memory);
}


struct SimpleStringTester : ::testing::Test
{
};

TEST_F(SimpleStringTester, constructionWithDefaultConstructor_expectedAllElementsAreZero)
{
    SimpleString text;

    ASSERT_EQ(0, text.size());
    ASSERT_EQ(0, text.capacity());
    ASSERT_STREQ("", text.data());
    ASSERT_STREQ("", text.c_str());
}

TEST_F(SimpleStringTester, constructionFromText_expectedDataCopied)
{
    /// text from: https://demotywatory.pl/4925253/Jesli-cos-ci-w-zyciu-nie-idzie-i-wpadasz-pyskiem-w-bloto
    constexpr const char* sourceText = "Jesli cos ci w zyciu nie idzie i wpadasz pyskiem w bloto, to musisz byc jak dzik - pchac to bloto ryjem do przodu";
    const auto sourceTextSize = strlen(sourceText);

    SimpleString text(sourceText);

    ASSERT_EQ(sourceTextSize, text.size());
    ASSERT_LE(sourceTextSize, text.capacity());
    ASSERT_STREQ(sourceText, text.data());
    ASSERT_STREQ(sourceText, text.c_str());
}

TEST_F(SimpleStringTester, constructionFromEmptyText_expectedEmptyTextCopied)
{
    constexpr const char* sourceText = "";
    const auto sourceTextSize = strlen(sourceText);

    SimpleString text(sourceText);

    ASSERT_EQ(sourceTextSize, text.size());
    ASSERT_LE(sourceTextSize, text.capacity());
    ASSERT_STREQ(sourceText, text.data());
    ASSERT_STREQ(sourceText, text.c_str());
}

TEST_F(SimpleStringTester, copyConstruction_expectedDataCopied)
{
    /// Quote: Einstein:
    constexpr const char* sourceText = "Wszystko powinno byc tak proste, jak to tylko mozliwe, ale nie prostsze";
    const auto sourceTextSize = strlen(sourceText);

    SimpleString text1(sourceText);
    SimpleString text2(text1);

    ASSERT_EQ(sourceTextSize, text1.size());
    ASSERT_LE(sourceTextSize, text1.capacity());
    ASSERT_STREQ(sourceText, text1.data());
    ASSERT_STREQ(sourceText, text1.c_str());

    ASSERT_EQ(sourceTextSize, text2.size());
    ASSERT_LE(sourceTextSize, text2.capacity());
    ASSERT_STREQ(sourceText, text2.data());
    ASSERT_STREQ(sourceText, text2.c_str());
}

TEST_F(SimpleStringTester, destructor_expectedMemoryFreed)
{
    // source: https://www.cytaty.info/autor/terrypratchett-3.htm
    const char quote[] =   "Uniwersytety sa skarbnicami wiedzy: studenci przychodza ze szkol przekonani, \n"
                           "ze wiedza juz prawie wszystko; po latach odchodza pewni, ze nie wiedza praktycznie niczego. \n"
                           "Gdzie sie podziewa ta wiedza? Zostaje na uniwersytecie, gdzie jest starannie suszona \n"
                           "i skladana w magazynach. \n";

    decltype(::allocations) allocationsBefore = ::allocations;
    decltype(::deallocations) deallocationsBefore = ::deallocations;

    {
        SimpleString text(quote);
        static_cast<void>(text); /// to remove warning because of not used variable

        allocationsBefore = ::allocations;
        deallocationsBefore = ::deallocations;
    }

    ASSERT_EQ(deallocationsBefore + 1, ::deallocations);
    ASSERT_LE(allocationsBefore, ::allocations);
}

TEST_F(SimpleStringTester, instanceMethod_expectedCountedAllLivingInstances)
{
    const auto instancesBefore = SimpleString::instances();

    ASSERT_EQ(0, SimpleString::instances());

    {
        SimpleString text1;
        ASSERT_EQ(1, text1.instances());
    }
    ASSERT_EQ(0, SimpleString::instances());

    constexpr size_t instances2Create = 10;
    SimpleString textInstances[instances2Create];
    ASSERT_EQ(instances2Create, SimpleString::instances());
}

TEST_F(SimpleStringTester, assign_expectedNewTextSet)
{
    // source of quote: Sw. Antoni Pustelnik:
    const char quote1[] = "Przyjda takie czasy, ze ludzie beda szaleni "
                          "i gdy zobacza kogos przy zdrowych zmyslach, "
                          "powstana przeciw niemu mowiac: "
                          "Jestes szalony bo nie jestes do nas podobny.";
    const auto quote1Length = strlen(quote1);

    // source: Sw. Jan Pawel II
    const char quote2[] = "Przyszlosc zaczyna sie dzisiaj, nie jutro";
    const auto quote2Length = strlen(quote2);

    SimpleString text(quote1);

    ASSERT_EQ(quote1Length, text.size());
    ASSERT_LE(quote1Length, text.capacity());
    ASSERT_STREQ(quote1, text.data());
    ASSERT_STREQ(quote1, text.c_str());


    text.assign(quote2);

    ASSERT_EQ(quote2Length, text.size());
    ASSERT_LE(quote2Length, text.capacity());
    ASSERT_STREQ(quote2, text.data());
    ASSERT_STREQ(quote2, text.c_str());
}

TEST_F(SimpleStringTester, equalToWithoutIgnoringCases)
{
    /// each block should be separate test!
    { /// empty text
        constexpr const char emptyText[] = "";

        const SimpleString text1(emptyText);
        const SimpleString text2(emptyText);

        ASSERT_STREQ(text1.c_str(), text2.c_str());
        ASSERT_TRUE(text1.equal_to(text2));
    }

    { /// not empty text
        constexpr const char sourceText[] = ":)";
        const SimpleString text1(sourceText);
        const SimpleString text2(sourceText);

        ASSERT_STREQ(text1.c_str(), text2.c_str());
        ASSERT_TRUE(text1.equal_to(text2));
    }

    { /// different texts
        constexpr const char sourceText1[] = ":)";
        constexpr const char sourceText2[] = ":(";
        const SimpleString text1(sourceText1);
        const SimpleString text2(sourceText2);

        ASSERT_EQ(text1.size(), text2.size());
        ASSERT_FALSE(text1.equal_to(text2));
    }

    { /// different texts and different size of texts
        constexpr const char sourceText1[] = ":)";
        constexpr const char sourceText2[] = ":-)";
        const SimpleString text1(sourceText1);
        const SimpleString text2(sourceText2);

        ASSERT_FALSE(text1.equal_to(text2));
    }

}

TEST_F(SimpleStringTester, equalToWithDifferentCaseSettings)
{
    constexpr const char sourceText1[] = "To jest nasza ziemia!";
    constexpr const char sourceText2[] = "To jest nasza Ziemia!";

    /// each block should be separate test!
    {
        const SimpleString text1(sourceText1);
        const SimpleString text2(sourceText2);

        ASSERT_FALSE(text1.equal_to(text2, /*case_sensitive=*/true));
    }

    {
        const SimpleString text1(sourceText1);
        const SimpleString text2(sourceText2);

        ASSERT_TRUE(text1.equal_to(text2, /*case_sensitive=*/false));
    }
}

TEST_F(SimpleStringTester, appendOneTextAnotherOne_expectedBothTextMerged)
{
    /// inspiracja: https://www.sadistic.pl/cyps-albo-zyps-vt183512.htm
    constexpr const char sourceText1[] = "Cyps";
    constexpr const char sourceText2[] = " albo Zyps";
    string mergedText(sourceText1);
    mergedText.append(sourceText2);

    const SimpleString text1(sourceText1);
    const SimpleString text2(sourceText2);

    SimpleString textMerged(text1);
    textMerged.append(text2);

    ASSERT_EQ(textMerged.size(), text1.size() + text2.size());
    ASSERT_STREQ(mergedText.c_str(), textMerged.data());
    ASSERT_STREQ(mergedText.c_str(), textMerged.c_str());
}
