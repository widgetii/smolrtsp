#include <smolrtsp/types/request_uri.h>

#include <greatest.h>

static enum greatest_test_res assert_pending(CharSlice99 input) {
    SmolRTSP_RequestUri result;
    SmolRTSP_ParseResult res = SmolRTSP_RequestUri_parse(&result, input);
    ASSERT(SmolRTSP_ParseResult_is_partial(res));
    PASS();
}

static enum greatest_test_res assert_ok(CharSlice99 input, SmolRTSP_RequestUri expected) {
    SmolRTSP_RequestUri result;
    SmolRTSP_ParseResult res = SmolRTSP_RequestUri_parse(&result, input);
    ASSERT(SmolRTSP_ParseResult_is_complete(res));
    ASSERT(CharSlice99_primitive_eq(result, expected));
    PASS();
}

TEST parse_request_uri(void) {
    const CharSlice99 input = CharSlice99_from_str("http://example.com ");

    for (size_t i = 0; i < input.len - 1; i++) {
        CHECK_CALL(assert_pending(CharSlice99_update_len(input, i)));
    }

    CHECK_CALL(assert_ok(input, CharSlice99_from_str("http://example.com")));

    PASS();
}

SUITE(request_uri) {
    RUN_TEST(parse_request_uri);
}
