#include <catch2/catch_amalgamated.hpp>

#include "gnosis/fix.hpp"
#include "gnosis/math.hpp"
#include "gnosis/string.hpp"

template<typename T>
struct EqualsGnosisMatcher : Catch::Matchers::MatcherGenericBase {
    EqualsGnosisMatcher(const T& scalar, const T& eps):
        scalar(scalar), eps(eps) {}

    bool match(const T& other) const {
        return gnosis::equal(scalar, other, eps);
    }

    std::string describe() const override {
        return "Equals: " + gnosis::to_string(scalar);
    }

private:
    const T& scalar;
    const T& eps;
};

template<typename T>
EqualsGnosisMatcher<T> EqualsGnosis(const T& scalar, const T& eps) {
    return {scalar, eps};
}

TEST_CASE("float to Fix<int64_t, 32>", "[fix]") {
    using Fix = gnosis::Fix<int64_t, 32>;
    const float eps = 1e-5f;
    REQUIRE_THAT(static_cast<float>(Fix(.0f)), EqualsGnosis(.0f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(.2f)), EqualsGnosis(.2f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(.3f)), EqualsGnosis(.3f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(.5f)), EqualsGnosis(.5f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(.7f)), EqualsGnosis(.7f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(.002357f)), EqualsGnosis(.002357f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(5.2f)), EqualsGnosis(5.2f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(12345.4321f)), EqualsGnosis(12345.4321f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(-.0f)), EqualsGnosis(-.0f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(-.2f)), EqualsGnosis(-.2f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(-.3f)), EqualsGnosis(-.3f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(-.5f)), EqualsGnosis(-.5f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(-.7f)), EqualsGnosis(-.7f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(-.002357f)), EqualsGnosis(-.002357f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(-5.2f)), EqualsGnosis(-5.2f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(-12345.4321f)), EqualsGnosis(-12345.4321f, eps));
}

TEST_CASE("float to Fix<int32_t, 16>", "[fix]") {
    using Fix = gnosis::Fix<int32_t, 16>;
    const float eps = 1e-3f;
    REQUIRE_THAT(static_cast<float>(Fix(.0f)), EqualsGnosis(.0f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(.2f)), EqualsGnosis(.2f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(.3f)), EqualsGnosis(.3f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(.5f)), EqualsGnosis(.5f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(.7f)), EqualsGnosis(.7f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(.002357f)), EqualsGnosis(.002357f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(5.2f)), EqualsGnosis(5.2f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(12345.4321f)), EqualsGnosis(12345.4321f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(-.0f)), EqualsGnosis(-.0f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(-.2f)), EqualsGnosis(-.2f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(-.3f)), EqualsGnosis(-.3f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(-.5f)), EqualsGnosis(-.5f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(-.7f)), EqualsGnosis(-.7f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(-.002357f)), EqualsGnosis(-.002357f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(-5.2f)), EqualsGnosis(-5.2f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(-12345.4321f)), EqualsGnosis(-12345.4321f, eps));
}

TEST_CASE("float to Fix<int32_t, 20>", "[fix]") {
    using Fix = gnosis::Fix<int32_t, 20>;
    const float eps = 1e-3f;
    REQUIRE_THAT(static_cast<float>(Fix(.0f)), EqualsGnosis(.0f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(.2f)), EqualsGnosis(.2f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(.3f)), EqualsGnosis(.3f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(.5f)), EqualsGnosis(.5f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(.7f)), EqualsGnosis(.7f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(.002357f)), EqualsGnosis(.002357f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(5.2f)), EqualsGnosis(5.2f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(1234.4321f)), EqualsGnosis(1234.4321f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(-.0f)), EqualsGnosis(-.0f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(-.2f)), EqualsGnosis(-.2f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(-.3f)), EqualsGnosis(-.3f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(-.5f)), EqualsGnosis(-.5f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(-.7f)), EqualsGnosis(-.7f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(-.002357f)), EqualsGnosis(-.002357f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(-5.2f)), EqualsGnosis(-5.2f, eps));
    REQUIRE_THAT(static_cast<float>(Fix(-1234.4321f)), EqualsGnosis(-1234.4321f, eps));
}

TEST_CASE("add", "[fix]") {
    using Fix = gnosis::Fix<int64_t, 32>;
    const Fix eps(1e-5f);
    REQUIRE_THAT(Fix(2) + Fix(3), EqualsGnosis(Fix(5), eps));
    REQUIRE_THAT(Fix(-2) + Fix(-3), EqualsGnosis(Fix(-5), eps));
    REQUIRE_THAT(Fix(-2) + Fix(3), EqualsGnosis(Fix(1), eps));
    REQUIRE_THAT(Fix(2) + Fix(-3), EqualsGnosis(Fix(-1), eps));
    REQUIRE_THAT(Fix(.2f) + Fix(.3f), EqualsGnosis(Fix(.5f), eps));
    REQUIRE_THAT(Fix(-.2f) + Fix(-.3f), EqualsGnosis(Fix(-.5f), eps));
    REQUIRE_THAT(Fix(-.2f) + Fix(.3f), EqualsGnosis(Fix(.1f), eps));
    REQUIRE_THAT(Fix(.2f) + Fix(-.3f), EqualsGnosis(Fix(-.1f), eps));
}