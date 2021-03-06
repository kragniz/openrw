#include <boost/test/unit_test.hpp>
#include "test_globals.hpp"
#include <loaders/RWBinaryStream.hpp>

BOOST_AUTO_TEST_SUITE(RWBStreamTests)

BOOST_AUTO_TEST_CASE(iterate_stream_test)
{
	{
		auto d = Global::get().e->data->openFile("landstal.dff");
		
		RWBStream stream(d->data, d->length);
	
		RWBStream::ChunkID id = stream.getNextChunk();

		BOOST_REQUIRE_EQUAL( id, 0x0010 );

		auto inner = stream.getInnerStream();

		auto inner1 = inner.getNextChunk();

		BOOST_REQUIRE_EQUAL( inner1, 0x0001 );

		auto innerCursor = inner.getCursor();

		// This is a value inside in the Clump's struct header section.
		BOOST_CHECK_EQUAL( *(std::uint32_t*)innerCursor, 0x10 );
	}
}

BOOST_AUTO_TEST_SUITE_END()
