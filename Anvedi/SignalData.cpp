#include "SignalData.h"
#include <limits>
#include <numeric>

void SignalData::clear()
{
	m_data.clear();
	domain = nullptr;
	emit DataCleared();
}

void SignalData::add(DataMap data)
{
	if (!data.empty())
	{
		m_data.insert(make_move_iterator(data.begin()), make_move_iterator(data.end()));
		emit DataAdded(m_data);
	}
}

void SignalData::addEmptyIfNotExists(const QString& name)
{
	getOrInsert(name);
}

void SignalData::set(const QString& name, std::function<void(Signal&)> setter)
{
	auto& signal = get(name);
	setter(signal);
	emit SignalChanged(signal);
}

void SignalData::setColor(const QString& name, const QColor& col)
{
	auto& signal = get(name);
	signal.color = col;
	emit SignalColorChanged(signal);
}

void SignalData::setVisible(const QString& name, bool visible)
{
	auto& signal = get(name);
	signal.visible = visible;
	emit SignalVisibilityChanged(signal);
}

const Signal& SignalData::get(const QString& name) const
{
	return m_data.at(name);
}

Signal& SignalData::get(const QString& name)
{
	return m_data.at(name);
}

Signal& SignalData::getOrInsert(const QString& name)
{
	auto it = m_data.equal_range(name);
	if (it.first != it.second)
		return it.first->second;
	auto& inserted = m_data.emplace_hint(it.first, name, Signal{ name })->second;
	emit DataAdded(m_data);
	return inserted;
}

void SignalData::onSignals(std::function<void(const Signal&)> fun) const
{
	for (const auto& signal : m_data)
		fun(signal.second);
}

std::pair<qreal, size_t> SignalData::nearestDomainValueTo(qreal val) const
{
	if (domain)
	{
		const auto& x = domain->y;
		const auto it = std::lower_bound(x.begin(), x.end(), val);
		return{ *it, std::distance(x.begin(), it) };
	}
	return{ std::numeric_limits<qreal>::quiet_NaN(), 0u };
}

const Signal* SignalData::getDomain() const
{
	return domain;
}

void SignalData::setAsDomain(const QString& name)
{
	domain = &get(name);
	emit DomainChanged(*domain);
}