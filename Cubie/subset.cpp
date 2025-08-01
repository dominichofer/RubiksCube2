#include "subset.h"
#include "twister.h"

static const AllTwister<Corners, uint16_t> c_prm_table(
	&Corners::prm_index,
	[](uint16_t i) { return Corners::from_index(i, 0); },
	Corners::prm_size
);

static const AllTwister<EdgesCenter, uint8_t> e_slice_prm_table(
	&EdgesCenter::slice_prm_index,
	[](uint8_t i) { return EdgesCenter::from_index(i, 0, EdgesCenter{}.slice_loc_index(), 0); },
	EdgesCenter::slice_prm_size
);

static const AllTwister<EdgesCenter, uint16_t> e_non_slice_prm_table(
	&EdgesCenter::non_slice_prm_index,
	[](uint16_t i) { return EdgesCenter::from_index(0, i, EdgesCenter{}.slice_loc_index(), 0); },
	EdgesCenter::non_slice_prm_size
);

SubsetCube::SubsetCube(uint16_t c_prm, uint8_t e_slice_prm, uint16_t e_non_slice_prm) noexcept
	: c_prm(c_prm), e_slice_prm(e_slice_prm), e_non_slice_prm(e_non_slice_prm)
{
}

SubsetCube::SubsetCube(const Cube3x3& c) noexcept
	: c_prm(c.c_prm)
	, e_slice_prm(c.e_slice_prm)
	, e_non_slice_prm(c.e_non_slice_prm)
{
}

SubsetCube SubsetCube::twisted(Twist t) const
{
	return SubsetCube{
		c_prm_table(c_prm, t),
		e_slice_prm_table(e_slice_prm, t),
		e_non_slice_prm_table(e_non_slice_prm, t)
	};
}

bool SubsetCube::is_solved() const
{
	return *this == SubsetCube{};
}

SubsetCube SubsetCube::from_subset_index(uint64_t index)
{
	uint16_t e_non_slice_prm = index % EdgesCenter::non_slice_prm_size;
	index /= EdgesCenter::non_slice_prm_size;
	uint8_t e_slice_prm = index % EdgesCenter::slice_prm_size;
	index /= EdgesCenter::slice_prm_size;
	uint16_t c_prm = index * 2;

	bool e_is_odd = is_even_permutation(e_non_slice_prm) xor is_even_permutation(e_slice_prm);
	if (e_is_odd == is_even_permutation(c_prm))
		c_prm += 1;

	return SubsetCube{
		c_prm,
		e_slice_prm,
		e_non_slice_prm
	};
}

uint64_t SubsetCube::subset_index() const
{
	uint64_t index = c_prm / 2;
	index = index * EdgesCenter::slice_prm_size + e_slice_prm;
	index = index * EdgesCenter::non_slice_prm_size + e_non_slice_prm;
	return index;
}



static const AllTwister<Corners, uint16_t> c_ori_table(
	&Corners::ori_index,
	[](uint16_t i) { return Corners::from_index(0, i); },
	Corners::ori_size
);
static const AllTwister<EdgesCenter, uint16_t> e_ori_table(
	&EdgesCenter::ori_index,
	[](uint16_t i) { return EdgesCenter::from_index(0, 0, 0, i); },
	EdgesCenter::ori_size
);
static const AllTwister<EdgesCenter, uint16_t> e_slice_loc_table(
	[](const EdgesCenter& e) { return e.slice_loc_index(); },
	[](uint16_t i) { return EdgesCenter::from_index(0, 0, i, 0); },
	EdgesCenter::slice_loc_size
);

CosetNumberCube::CosetNumberCube(uint16_t c_ori, uint16_t e_ori, uint16_t e_slice_loc) noexcept
	: c_ori(c_ori), e_ori(e_ori), e_slice_loc(e_slice_loc)
{
}

CosetNumberCube::CosetNumberCube(const Cube3x3& c) noexcept
	: c_ori(c.c_ori)
	, e_ori(c.e_ori)
	, e_slice_loc(c.e_slice_loc)
{
}

CosetNumberCube CosetNumberCube::impossible() noexcept
{
	return CosetNumberCube{
		std::numeric_limits<uint16_t>::max(),
		std::numeric_limits<uint16_t>::max(),
		std::numeric_limits<uint16_t>::max()
	};
}

CosetNumberCube CosetNumberCube::twisted(Twist t) const
{
	return CosetNumberCube{
		c_ori_table(c_ori, t),
		e_ori_table(e_ori, t),
		e_slice_loc_table(e_slice_loc, t)
	};
}

bool CosetNumberCube::in_subset() const
{
	return *this == CosetNumberCube{ 0, 0, 494 };
}

CosetNumberCube CosetNumberCube::from_coset_number(uint32_t number)
{
	uint16_t e_slice_loc = number % EdgesCenter::slice_loc_size;
	number /= EdgesCenter::slice_loc_size;
	uint16_t e_ori = number % EdgesCenter::ori_size;
	number /= EdgesCenter::ori_size;
	uint16_t c_ori = number;
	return CosetNumberCube{
		c_ori,
		e_ori,
		e_slice_loc
	};
}

uint32_t CosetNumberCube::coset_number() const
{
	uint32_t number = c_ori;
	number = number * EdgesCenter::ori_size + e_ori;
	number = number * EdgesCenter::slice_loc_size + e_slice_loc;
	return number;
}

uint64_t CosetNumberCube::hash() const
{
	return (static_cast<uint64_t>(c_ori) << 32) | (static_cast<uint64_t>(e_ori) << 16) | e_slice_loc;
}



//static const AllTwister<Corners, uint16_t> c_prm_table(
//	H0_twists,
//	&Corners::prm_index,
//	[](uint16_t i) { return Corners::from_index(i, 0); },
//	Corners::prm_size
//);
//
//static const AllTwister<EdgesCenter, uint8_t> e_slice_prm_table(
//	H0_twists,
//	&EdgesCenter::slice_prm_index,
//	[](uint16_t i) { return EdgesCenter::from_index(i, 0, EdgesCenter{}.slice_loc_index(), 0); },
//	EdgesCenter::slice_prm_size
//);
//
//static const AllTwister<EdgesCenter, uint16_t> e_non_slice_prm_table(
//	H0_twists,
//	&EdgesCenter::non_slice_prm_index,
//	[](uint16_t i) { return EdgesCenter::from_index(0, i, EdgesCenter{}.slice_loc_index(), 0); },
//	EdgesCenter::non_slice_prm_size
//);
//
//CosetIndexCube::CosetIndexCube(uint16_t c_prm, uint8_t e_slice_prm, uint16_t e_non_slice_prm) noexcept
//	: c_prm(c_prm), e_slice_prm(e_slice_prm), e_non_slice_prm(e_non_slice_prm)
//{
//}
//
//CosetIndexCube::CosetIndexCube(const Corners& c, const EdgesCenter& e) noexcept
//	: c_prm(c.prm_index())
//	, e_slice_prm(e.slice_prm_index())
//	, e_non_slice_prm(e.non_slice_prm_index())
//{
//}
//
//CosetIndexCube::CosetIndexCube() noexcept
//	: CosetIndexCube(Corners{}, EdgesCenter{})
//{
//}
