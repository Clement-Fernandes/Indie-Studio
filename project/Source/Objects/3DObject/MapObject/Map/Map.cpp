/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Map
*/

#include "Map.hpp"

Object::Map::Map(std::vector<Object::Render::MyModel> models, std::vector<Object::Render::MyTexture> texture) : _isEnable(true)
{
    _mapTextures = texture;
    _mapModels = models;
}

Object::Map::Map(std::vector<Object::Render::MyModel> models, std::vector<Object::Render::MyTexture> texture, Position const &position) : _isEnable(true)
{
    _mapPosition = position;
    _blockSize = 10.0f;
}

Object::Map::~Map()
{
}

void Object::Map::createFile(const std::string &filename)
{
    _file.open(filename, std::ios::out);
    if (!_file) {
        _file.close();
        throw Error::FileError("file failed to open " + filename);
    }
}

void Object::Map::printLine(std::size_t height)
{
    for (size_t one = 0; one < height + 2; one++) {
        _file << static_cast<char>(MAP_OBJECTS::WALL_SIDE);
    }
    _file << std::endl;
}

std::vector<Position> Object::Map::getMapCorners(std::size_t width, std::size_t height)
{
    std::vector<Position> corners;

    width * _blockSize;
    corners.push_back({10.0f, 0.0f, 10.0f});
    corners.push_back({static_cast<float>(width * 10), 0.0f, 10.0f});
    corners.push_back({10.0f, 0.0f, static_cast<float>(height * 10)});
    corners.push_back({static_cast<float>(width * 10), 0.0f, static_cast<float>(height * 10)});
    return corners;
}

void Object::Map::generate(const std::string &filename, std::size_t width, std::size_t height, std::size_t percentageDrop)
{
    srand(time(NULL));
    std::size_t randomNumber = 1 + (rand() % 100);

    if ((width % 2) == 0 || (height % 2) == 0)
        throw Error::Errors("Height and Width are not compatible !");
    createFile(filename);
    printLine(height);
    for (size_t x = 0; x < height; x++) {
        _file << static_cast<char>(MAP_OBJECTS::WALL_SIDE);
        for (size_t y = 0; y < width; y++) {
            if (x % 2 && y % 2)
                _file << static_cast<char>(MAP_OBJECTS::WALL_MIDDLE);
            else {
                randomNumber = 1 + (rand() % 100);
                if (randomNumber > percentageDrop || (x <= 1 || x >= height - 2) && (y <= 1 || y >= width - 2))
                    _file << static_cast<char>(MAP_OBJECTS::EMPTY);
                else
                    _file << static_cast<char>(MAP_OBJECTS::BOX);
            }
        }
        _file << static_cast<char>(MAP_OBJECTS::WALL_SIDE);
        _file << std::endl;
    }
    printLine(height);
}

void Object::Map::draw()
{
    for (int index = 0; index < _mapPositionsObjects.size(); index++) {
        for (int idx = 0; idx < _mapPositionsObjects[index].size(); idx++) {
            _mapPositionsObjects[index][idx]->draw();

        }
    }
    for (int index = 0; index < _groundMap.size(); index++) {
        for (int idx = 0; idx < _groundMap[index].size(); idx++) {
            _groundMap[index][idx]->draw();

        }
    }
}

std::vector<std::string> Object::Map::load(std::string const &pathToFile)
{
    std::ifstream file(pathToFile);
    std::string tmp;
    std::vector<std::string> map;

    if (map.empty()) {
        if (!file.is_open())
            throw Error::FileError("File " + pathToFile + " doesn't exist");
        while (std::getline(file, tmp))
            map.push_back(tmp);
        file.close();
    }
    return (map);
}

void Object::Map::removeBlock(std::size_t index)
{
    if (_mapObjects.at(index)->getType() == MAP_OBJECTS::BOX)
        _mapObjects.erase(_mapObjects.begin() + index);
}

void Object::Map::process(std::string const &pathToFile)
{
    _pathToMap = pathToFile;

    std::vector<std::string> mapLayout = load(_pathToMap);

    static const std::map<Object::MAP_OBJECTS, std::pair<Object::Render::MyModel, Object::Render::MyTexture>> keyMap = {
        {MAP_OBJECTS::WALL_MIDDLE, {_mapModels.at(4), _mapTextures.at(6)}},
        {MAP_OBJECTS::GROUND, {_mapModels.at(5), _mapTextures.at(7)}},
        {MAP_OBJECTS::WALL_SIDE, {_mapModels.at(6), _mapTextures.at(8)}},
        {MAP_OBJECTS::BOX, {_mapModels.at(7), _mapTextures.at(9)}},
        {MAP_OBJECTS::EMPTY, {_mapModels.at(8), _mapTextures.at(10)}}
    };

    srand(time(NULL));

    _blockSize = 10.0f;
    _mapDimensions.setX((mapLayout.size() * _blockSize) / 2);
    _mapDimensions.setY(0);
    _mapDimensions.setZ((mapLayout[0].size() * _blockSize) / 2);
    std::cout <<_mapDimensions<<std::endl;

    Vector3 tilePosition = {0, 0, 0};

    for (std::size_t line = 0; line < mapLayout.size(); line += 1) {
        std::vector<std::shared_ptr<AThreeDimensionObject>> tempVector;
        std::vector<std::shared_ptr<AThreeDimensionObject>> tempGrass;
        for (std::size_t col = 0; col < mapLayout.at(line).size(); col++) {
            if (keyMap.find(static_cast<MAP_OBJECTS>(mapLayout.at(line).at(col))) != keyMap.end())
                tempVector.emplace_back(std::make_shared<Object::Block>(keyMap.at(static_cast<MAP_OBJECTS>(mapLayout.at(line).at(col))).first, keyMap.at(static_cast<MAP_OBJECTS>(mapLayout.at(line).at(col))).second, (Position){tilePosition.x, tilePosition.y, tilePosition.z}, static_cast<MAP_OBJECTS>(mapLayout.at(line).at(col))));
            if (mapLayout.at(line).at(col) == static_cast<char>(Object::MAP_OBJECTS::WALL_SIDE))
                tempGrass.emplace_back(std::make_shared<Object::Block>(keyMap.at(MAP_OBJECTS::WALL_SIDE).first, keyMap.at(MAP_OBJECTS::WALL_SIDE).second, (Position){tilePosition.x, tilePosition.y - _blockSize, tilePosition.z}, MAP_OBJECTS::WALL_SIDE));
            else
                tempGrass.emplace_back(std::make_shared<Object::Block>(keyMap.at(MAP_OBJECTS::GROUND).first, keyMap.at(MAP_OBJECTS::GROUND).second, (Position){tilePosition.x, tilePosition.y - (_blockSize - 1), tilePosition.z}, MAP_OBJECTS::GROUND));
            tilePosition.x += _blockSize;
        }
        _mapPositionsObjects.emplace_back(tempVector);
        _groundMap.emplace_back(tempGrass);
        tilePosition.z += _blockSize;
        tilePosition.x = 0;
        tempVector.emplace_back(std::make_shared<Object::Block>(keyMap.at(MAP_OBJECTS::BOX).first, keyMap.at(MAP_OBJECTS::BOX).second, (Position){tilePosition.x, tilePosition.y, tilePosition.z}, MAP_OBJECTS::BOX));
    }
}

int Object::Map::roundUp(int nb, int multiple)
{
    if (multiple == 0)
        return nb;

    int remainder = abs(nb) % multiple;

    if (remainder == 0)
        return nb;

    if (nb < 0)
        return (-(abs(nb) - remainder));
    else
        return (nb + multiple - remainder);
}

Object::MAP_OBJECTS Object::Map::isColliding(Position &direction, Position playerPosition)
{
    Position temppos = playerPosition;
    temppos +=  direction;

    std::pair<int, int> position = transposeFrom3Dto2D(temppos);
    return (_mapPositionsObjects.at(position.second).at(position.first)->getType());
}

std::pair<int, int> Object::Map::transposeFrom3Dto2D(Position const &position)
{
    int x = roundUp(static_cast<int>(position.getX()), (_blockSize / 2));
    int z = roundUp(static_cast<int>(position.getZ()), (_blockSize / 2));

    if (x % 10 == (_blockSize / 2))
        x -= 5;
    if (z % 10 == (_blockSize / 2))
        z -= 5;
    return {x / 10, z / 10};
}

void Object::Map::exploseBomb(Position const &position, int radius)
{
    // std::size_t percentageBonusDrop = 30;
    std::pair<int, int> blockPosition = transposeFrom3Dto2D(position);
    float blockSize = _blockSize;
    std::vector<bool> alreadyDestroyed = { false, false, false, false };
    Position blockToPlace;
    std::vector<std::pair<int, int>> target = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    std::size_t index = 0;

    for (std::size_t bombRange = 1; bombRange < radius + 1; bombRange++) {
        index = 0;
        for (auto &[x, y] : target) {
            if ((blockPosition.second + (y * bombRange)) > 0 && (blockPosition.second + (y * bombRange)) < _mapPositionsObjects.size())
                if ((blockPosition.first + (x * bombRange)) > 0 && (blockPosition.first + (x * bombRange)) < _mapPositionsObjects.at(blockPosition.second + (y * bombRange)).size()) {
                    if (_mapPositionsObjects.at(blockPosition.second + (y * bombRange)).at(blockPosition.first + (x * bombRange))->getType() == Object::MAP_OBJECTS::WALL_MIDDLE)
                        alreadyDestroyed.at(index) = true;
                    if (_mapPositionsObjects.at(blockPosition.second + (y * bombRange)).at(blockPosition.first + (x * bombRange))->getType() == Object::MAP_OBJECTS::BOX && !alreadyDestroyed.at(index)) {
                        blockToPlace = {static_cast<float>((blockPosition.first +  (x * bombRange)) * 10), 0, static_cast<float>((blockPosition.second +(y * bombRange)) * 10)};
                        placeObjectInMap<Object::Block>({blockPosition.first + (x * bombRange), blockPosition.second + (y * bombRange)}, std::make_shared<Object::Block>(_mapModels.at(8), _mapTextures.at(10), blockToPlace, Object::MAP_OBJECTS::EMPTY));
                        alreadyDestroyed.at(index) = true;
                    }
                }
            index++;
        }
}
        // if (_mapPositionsObjects.at(blockPosition.second).at(blockPosition.first + 1)->getType() == Object::MAP_OBJECTS::BOX && alreadyDestroyed.at(0) == false) {
        //     blockToPlace = (Position){static_cast<float>((blockPosition.first +  1) * 10), 0, static_cast<float>(blockPosition.second * 10)};
        //     placeObjectInMap<Object::Block>({blockPosition.first + 1, blockPosition.second}, std::make_shared<Object::Block>(_mapModels.at(8), _mapTextures.at(10), blockToPlace, Object::MAP_OBJECTS::EMPTY));
        //     alreadyDestroyed.at(0) = true;
        // }

        // if (_mapPositionsObjects.at(blockPosition.second).at(blockPosition.first - 1)->getType() == Object::MAP_OBJECTS::BOX && alreadyDestroyed.at(1) == false) {
        //     blockToPlace = (Position){static_cast<float>((blockPosition.first - 1) * 10), 0, static_cast<float>(blockPosition.second * 10)};
        //     placeObjectInMap<Object::Block>({blockPosition.first - 1, blockPosition.second}, std::make_shared<Object::Block>(_mapModels.at(8), _mapTextures.at(10), blockToPlace, Object::MAP_OBJECTS::EMPTY));
        //     alreadyDestroyed.at(1) = true;
        // }

        // if (_mapPositionsObjects.at(blockPosition.second + 1).at(blockPosition.first)->getType() == Object::MAP_OBJECTS::BOX && alreadyDestroyed.at(2) == false) {
        //     blockToPlace = (Position){static_cast<float>((blockPosition.first + 1) * 10), 0, static_cast<float>(blockPosition.second * 10)};
        //     placeObjectInMap<Object::Block>({blockPosition.first, blockPosition.second + 1}, std::make_shared<Object::Block>(_mapModels.at(8), _mapTextures.at(10), blockToPlace, Object::MAP_OBJECTS::EMPTY));
        //     alreadyDestroyed.at(2) = true;
        // }

        // if (_mapPositionsObjects.at(blockPosition.second - 1).at(blockPosition.first)->getType() == Object::MAP_OBJECTS::BOX && alreadyDestroyed.at(3) == false) {
        //     blockToPlace = (Position){static_cast<float>((blockPosition.first - 1) * 10), 0, static_cast<float>(blockPosition.second * 10)};
        //     placeObjectInMap<Object::Block>({blockPosition.first, blockPosition.second - 1}, std::make_shared<Object::Block>(_mapModels.at(8), _mapTextures.at(10), blockToPlace, Object::MAP_OBJECTS::EMPTY));
        //     alreadyDestroyed.at(3) = true;
        // }
    // }
}
