#pragma once
#include <cstdint>
#include <string>
#include <vector>

enum class Twist : uint8_t
{
	L1, L2, L3, l1, l2, l3,
	R1, R2, R3, r1, r2, r3,
	U1, U2, U3, u1, u2, u3,
	D1, D2, D3, d1, d2, d3,
	F1, F2, F3, f1, f2, f3,
	B1, B2, B3, b1, b2, b3,
	None
};

std::string to_string(Twist);

Twist inversed(Twist);
std::vector<Twist> inversed(const std::vector<Twist>&);

template <typename Derived>
class Twistable
{
public:
	auto operator<=>(const Twistable&) const = default;

	virtual Derived twisted(Twist) const = 0;
	Derived twisted(const std::vector<Twist>& twists) const
	{
		auto result = static_cast<const Derived&>(*this);
		for (auto twist : twists)
			result = result.twisted(twist);
		return result;
	}
	template <typename... Twists>
	Derived twisted(Twist twist, Twists... twists) const
	{
		return twisted(twist).twisted(twists...);
	}

	Derived L1() const { return twisted(Twist::L1); }
	Derived L2() const { return twisted(Twist::L2); }
	Derived L3() const { return twisted(Twist::L3); }
	Derived l1() const { return twisted(Twist::l1); }
	Derived l2() const { return twisted(Twist::l2); }
	Derived l3() const { return twisted(Twist::l3); }
	Derived R1() const { return twisted(Twist::R1); }
	Derived R2() const { return twisted(Twist::R2); }
	Derived R3() const { return twisted(Twist::R3); }
	Derived r1() const { return twisted(Twist::r1); }
	Derived r2() const { return twisted(Twist::r2); }
	Derived r3() const { return twisted(Twist::r3); }
	Derived U1() const { return twisted(Twist::U1); }
	Derived U2() const { return twisted(Twist::U2); }
	Derived U3() const { return twisted(Twist::U3); }
	Derived u1() const { return twisted(Twist::u1); }
	Derived u2() const { return twisted(Twist::u2); }
	Derived u3() const { return twisted(Twist::u3); }
	Derived D1() const { return twisted(Twist::D1); }
	Derived D2() const { return twisted(Twist::D2); }
	Derived D3() const { return twisted(Twist::D3); }
	Derived d1() const { return twisted(Twist::d1); }
	Derived d2() const { return twisted(Twist::d2); }
	Derived d3() const { return twisted(Twist::d3); }
	Derived F1() const { return twisted(Twist::F1); }
	Derived F2() const { return twisted(Twist::F2); }
	Derived F3() const { return twisted(Twist::F3); }
	Derived f1() const { return twisted(Twist::f1); }
	Derived f2() const { return twisted(Twist::f2); }
	Derived f3() const { return twisted(Twist::f3); }
	Derived B1() const { return twisted(Twist::B1); }
	Derived B2() const { return twisted(Twist::B2); }
	Derived B3() const { return twisted(Twist::B3); }
	Derived b1() const { return twisted(Twist::b1); }
	Derived b2() const { return twisted(Twist::b2); }
	Derived b3() const { return twisted(Twist::b3); }
};
