/*
 * Copyright 2010 OpenXcom Developers.
 *
 * This file is part of OpenXcom.
 *
 * OpenXcom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenXcom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenXcom.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "Unit.h"

namespace OpenXcom
{

void operator>> (const YAML::Node& node, UnitStats& stats)
{
	node["tu"] >> stats.tu;
	node["stamina"] >> stats.stamina;
	node["health"] >> stats.health;
	node["bravery"] >> stats.bravery;
	node["reactions"] >> stats.reactions;
	node["firing"] >> stats.firing;
	node["throwing"] >> stats.throwing;
	node["strength"] >> stats.strength;
	node["psiStrength"] >> stats.psiStrength;
	node["psiSkill"] >> stats.psiSkill;
	node["melee"] >> stats.melee;
}

YAML::Emitter& operator<< (YAML::Emitter& out, const UnitStats& stats)
{
	out << YAML::BeginMap;
    out << YAML::Key << "tu" << YAML::Value << stats.tu;
	out << YAML::Key << "stamina" << YAML::Value << stats.stamina;
	out << YAML::Key << "health" << YAML::Value << stats.health;
	out << YAML::Key << "bravery" << YAML::Value << stats.bravery;
	out << YAML::Key << "reactions" << YAML::Value << stats.reactions;
	out << YAML::Key << "firing" << YAML::Value << stats.firing;
	out << YAML::Key << "throwing" << YAML::Value << stats.throwing;
	out << YAML::Key << "strength" << YAML::Value << stats.strength;
	out << YAML::Key << "psiStrength" << YAML::Value << stats.psiStrength;
	out << YAML::Key << "psiSkill" << YAML::Value << stats.psiSkill;
	out << YAML::Key << "melee" << YAML::Value << stats.melee;
	out << YAML::EndMap;
    return out;
}

/**
 * Creates a certain type of unit.
 * @param type String defining the type.
 * @param race String defining the race.
 * @param rank String defining the rank.
 */
Unit::Unit(const std::string &type, std::string race, std::string rank) : _type(type), _race(race), _rank(rank), _stats(), _armor(""), _standHeight(0), _kneelHeight(0), _loftemps(0), _value(0), _deathSound(0), _intelligence(0), _aggression(0), _specab(SPECAB_NONE)
{
}

/**
 *
 */
Unit::~Unit()
{

}

/**
 * Loads the unit from a YAML file.
 * @param node YAML node.
 */
void Unit::load(const YAML::Node &node)
{
	int a = 0;

	for (YAML::Iterator i = node.begin(); i != node.end(); ++i)
	{
		std::string key;
		i.first() >> key;
		if (key == "type")
		{
			i.second() >> _type;
		}
		else if (key == "race")
		{
			i.second() >> _race;
		}
		else if (key == "rank")
		{
			i.second() >> _rank;
		}
		else if (key == "stats")
		{
			i.second() >> _stats;
		}
		else if (key == "armor")
		{
			i.second() >> _armor;
		}
		else if (key == "standHeight")
		{
			i.second() >> _standHeight;
		}
		else if (key == "kneelHeight")
		{
			i.second() >> _kneelHeight;
		}
		else if (key == "loftemps")
		{
			i.second() >> _loftemps;
		}
		else if (key == "value")
		{
			i.second() >> _value;
		}
		else if (key == "deathSound")
		{
			i.second() >> _deathSound;
		}
		else if (key == "intelligence")
		{
			i.second() >> _intelligence;
		}
		else if (key == "aggression")
		{
			i.second() >> _aggression;
		}
		else if (key == "specab")
		{
			i.second() >> a;
			_specab = (SpecialAbility)a;
		}
	}
}

/**
 * Saves the unit to a YAML file.
 * @param out YAML emitter.
 */
void Unit::save(YAML::Emitter &out) const
{
	out << YAML::BeginMap;
	out << YAML::Key << "type" << YAML::Value << _type;
	out << YAML::Key << "race" << YAML::Value << _race;
	out << YAML::Key << "rank" << YAML::Value << _rank;
	out << YAML::Key << "stats" << YAML::Value << _stats;
	out << YAML::Key << "armor" << YAML::Value << _armor;
	out << YAML::Key << "standHeight" << YAML::Value << _standHeight;
	out << YAML::Key << "kneelHeight" << YAML::Value << _kneelHeight;
	out << YAML::Key << "loftemps" << YAML::Value << _loftemps;
	out << YAML::Key << "value" << YAML::Value << _value;
	out << YAML::Key << "deathSound" << YAML::Value << _deathSound;
	out << YAML::Key << "intelligence" << YAML::Value << _intelligence;
	out << YAML::Key << "aggression" << YAML::Value << _aggression;
	out << YAML::Key << "specab" << YAML::Value << _specab;
	out << YAML::EndMap;
}

/**
 * Returns the language string that names
 * this unit. Each unit type has a unique name.
 * @return Unit name.
 */
std::string Unit::getType() const
{
	return _type;
}

/**
 * Sets the unit's stats data object.
 * @param Stats.
 */
void Unit::setStats(struct UnitStats stats)
{
	_stats = stats;
}

/**
 * Sets the unit's armor type.
 * @param string.
 */
void Unit::setArmor(const std::string &armor)
{
	_armor = armor;
}

/**
 * Set the unit's height at standing, kneeling and 3D template.
 * @param string.
 */
void Unit::setVoxelParameters(int standHeight, int kneelHeight, int loftemps)
{
	_standHeight = standHeight;
	_kneelHeight = kneelHeight;
	_loftemps = loftemps;
}

/**
 * Set the unit's intelligence and aggression.
 * @param string.
 */
void Unit::setAIParameters(int intelligence, int aggression)
{
	_intelligence = intelligence;
	_aggression = aggression;
}

/**
 * Set the unit's special ability.
 * @param specab.
 */
void Unit::setSpecialAbility(SpecialAbility specab)
{
	_specab = specab;
}

/**
 * Returns the unit's stats data object.
 * @return Stats.
 */
UnitStats *Unit::getStats()
{
	return &_stats;
}

/**
 * Returns the unit's height at standing.
 * @return height.
 */
int Unit::getStandHeight() const
{
	return _standHeight;
}

/**
 * Returns the unit's height at kneeling.
 * @return height.
 */
int Unit::getKneelHeight() const
{
	return _kneelHeight;
}

/**
 * Returns the unit's 3D template ID.
 * @return template ID.
 */
int Unit::getLoftemps() const
{
	return _loftemps;
}

/**
 * Gets the unit's armor type.
 * @return string.
 */
std::string Unit::getArmor() const
{
	return _armor;
}

/**
 * Gets the alien's race.
 * @return string.
 */
std::string Unit::getRace() const
{
	return _race;
}

/**
 * Gets the alien's rank.
 * @return string.
 */
std::string Unit::getRank() const
{
	return _rank;
}

/**
 * Set the unit's value - for scoring.
 * @param value.
 */
void Unit::setValue(int value)
{
	_value = value;
}

/**
 * Get the unit's value - for scoring.
 * @return value.
 */
int Unit::getValue() const
{
	return _value;
}

/**
 * Set the unit's death sound.
 * @param id.
 */
void Unit::setDeathSound(int id)
{
	_deathSound = id;
}

/**
 * Get the unit's death sound.
 * @return id.
 */
int Unit::getDeathSound() const
{
	return _deathSound;
}

/**
 * Get the intelligence. This is the number of turns AI remembers your troops position.
 * @return intelligence.
 */
int Unit::getIntelligence() const
{
	return _intelligence;
}

/**
 * Get the aggression. Determines the chance of revenge and taking cover.
 * @return intelligence.
 */
int Unit::getAggression() const
{
	return _aggression;
}

/**
 * Get the unit's special ability.
 * @return specab.
 */
int Unit::getSpecialAbility() const
{
	return (int)_specab;
}

}
