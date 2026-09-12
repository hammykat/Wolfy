#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include "GameTypes.hpp"

struct Vector2Hash
{
    std::size_t operator()(const Blokk::Vector2& Coord) const noexcept
    {
        return
            (static_cast<uint64_t>(static_cast<uint32_t>(Coord.x)) << 32) |
            static_cast<uint32_t>(Coord.y);
    }
};

template <typename Type>
class Tree
{

public: // Allow full access to data

    std::vector<std::vector<Type>> Values;

    std::unordered_map<Blokk::Vector2, uint32_t, Vector2Hash> GroupNames;

    std::vector<std::vector<uint32_t>> FreeIdxs;
    std::vector<uint32_t> FreeIdxSize;

    [[nodiscard]]
    Type GetItemFromGroup(const Blokk::Vector2& GroupCoords, uint32_t Idx)
    {
        return Values[GroupNames.at(GroupCoords)][Idx];
    }

    [[nodiscard]]
    Type GetItemFromGroup(uint32_t GroupIdx, uint32_t Idx)
    {
        return Values[GroupIdx][Idx];
    }

    void AddItemToGroup(
        const Blokk::Vector2& GroupCoords,
        Type Val)
    {
        uint32_t Idx = GroupNames.at(GroupCoords);

        if (FreeIdxSize[Idx] > 0)
        {
            uint32_t FreeIdx = FreeIdxs[Idx].back();
            FreeIdxs[Idx].pop_back();

            Values[Idx][FreeIdx] = Val;
            --FreeIdxSize[Idx];
        }
        else
        {
            Values[Idx].push_back(Val);
        }
    }

    void AddItemsToGroup(
        const Blokk::Vector2& GroupCoords,
        const std::vector<Type>& Items)
    {
        uint32_t Idx = GroupNames.at(GroupCoords);

        for (const auto& Val : Items)
        {
            if (FreeIdxSize[Idx] > 0)
            {
                uint32_t FreeIdx = FreeIdxs[Idx].back();
                FreeIdxs[Idx].pop_back();

                Values[Idx][FreeIdx] = Val;
                --FreeIdxSize[Idx];
            }
            else
            {
                Values[Idx].push_back(Val);
            }
        }
    }

    void CreateNewGroup(const Blokk::Vector2& GroupCoords)
    {
        uint32_t Idx = static_cast<uint32_t>(Values.size());

        GroupNames.emplace(GroupCoords, Idx);

        Values.emplace_back();
        FreeIdxs.emplace_back();
        FreeIdxSize.push_back(0);
    }

    void RemoveItemFromGroup(
        const Blokk::Vector2& GroupCoords,
        uint32_t Idx
    ) {
        uint32_t GroupIdx = GroupNames.at(GroupCoords);

        FreeIdxs[GroupIdx].push_back(Idx);
        ++FreeIdxSize[GroupIdx];
    }

    void RemoveItemFromGroup(
        uint32_t GroupIdx,
        uint32_t Idx
    ) {
        FreeIdxs[GroupIdx].push_back(Idx);
        ++FreeIdxSize[GroupIdx];
    }

    Type& GetRefToGroup(const Blokk::Vector2& GroupCoords)
    {
        uint32_t GroupIdx = GroupNames.at(GroupCoords);

        return Values[GroupIdx];
    }

    uint32_t GetIndexOfGroup(const Blokk::Vector2& GroupCoords)
    {
        return GroupNames.at(GroupCoords);
    }
};