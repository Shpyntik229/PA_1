#pragma once
#include <array>
#include <chrono>

constexpr int MAX_DEPTH = 32;
typedef std::array<std::array<int8_t, 3>, 3> Field;
struct Coords { int i; int j; };
enum Pos {
    Unknown,

    Up,
    Down,
    Left,
    Right
};

bool isCorrect(const Field& field);

Coords find_empty(const Field& field);

class Logger
{
public:
	Logger() = default;

	inline std::size_t getIterationCount() const
	{
		return m_itercnt;
	}

	inline std::size_t getTime() const
	{
		return m_time;
	}

	inline std::size_t getConditionsCount() const {
		return m_condcnt;
	}

	inline std::size_t getConditionsInMemoryCount() const
	{
		return m_condinmemcnt;
	}

	inline void startTimer()
	{
		m_curtime = std::chrono::high_resolution_clock::now();
	}

	inline void stopTimer()
	{
		using namespace std::chrono;
		m_time = duration_cast<microseconds>(high_resolution_clock::now() - m_curtime).count();
	}

	inline void IncrementIterationCounter()
	{
		m_itercnt++;
	}

	inline void IncrementConditionCount()
	{
		m_condcnt++;
	}

	inline void setConditionInMemoryCount(std::size_t cnt)
	{
		m_condinmemcnt = cnt;
	}
private:
	std::size_t m_itercnt = 0, m_time = 0, m_condcnt = 0, m_condinmemcnt;
	std::chrono::time_point<std::chrono::steady_clock> m_curtime;
};

void decrementEachValue(Field& field);