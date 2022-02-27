#pragma once

namespace PFAV::Core
{
	struct Tile
	{
		enum class Type
		{
			eStart = 0,
			eEnd,
			eEmpty,
			eObstacle,
			eConsidered,
			ePath,

			TypesCount
		};

		explicit Tile(Type type = Type::eEmpty);

		Type type;
	};
}
