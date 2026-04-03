#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

class FileNotFoundException : public std::runtime_error {
public:
    FileNotFoundException(const std::string& filename) : std::runtime_error("파일을 찾을 수 없습니다: " + filename) {
    }
};

class CorruptedSaveException : public std::runtime_error {
public:
    CorruptedSaveException(const std::string& message) : std::runtime_error(message) {
    }
};

class InvalidStatException : public std::invalid_argument {
public:
    InvalidStatException(const std::string& message) : std::invalid_argument(message) {
    }
};

class Player {
private:
    std::string mName;
    int         mLevel;
    int         mHP;
    int         mGold;

public:
    Player(const std::string& name = "플레이어", int level = 1, int hp = 100, int gold = 0) : mName(name), mLevel(level), mHP(hp), mGold(gold) {
        if (mLevel < 1 || mLevel > 99) {
            throw InvalidStatException("레벨은 1~99 사이여야 합니다: " + std::to_string(mLevel));
        }
        if (mHP < 1 || mHP > 9999) {
            throw InvalidStatException("HP는 1~9999 사이여야 합니다: " + std::to_string(mHP));
        }
        if (mGold < 0) {
            throw InvalidStatException("골드는 0 이상이어야 합니다: " + std::to_string(mGold));
        }
    }

    void display() const {
        std::cout << "\n=== 플레이어 정보 ===" << std::endl;
        std::cout << "이름: " << mName << std::endl;
        std::cout << "레벨: " << mLevel << std::endl;
        std::cout << "HP: " << mHP << std::endl;
        std::cout << "골드: " << mGold << std::endl;
    }

    void save(const std::string& filename) const {
        std::ofstream file(filename);

        if (!file.is_open()) {
            throw std::runtime_error("파일을 저장할 수 없습니다: " + filename);
        }

        file << mName << "\n";
        file << mLevel << "\n";
        file << mHP << "\n";
        file << mGold << "\n";

        std::cout << "세이브 완료: " << filename << std::endl;
    }

    static Player load(const std::string& filename) {
        std::ifstream file(filename);

        if (!file.is_open()) {
            throw FileNotFoundException(filename);
        }

        std::string name;
        int         level;
        int         hp;
        int         gold;

        std::getline(file, name);

        file >> level >> hp >> gold;

        if (file.fail()) {
            throw CorruptedSaveException("세이브 파일이 손상되었습니다: " + filename);
        }

        std::cout << "로드 완료: " << filename << std::endl;

        return Player(name, level, hp, gold);
    }
};

class GameManager {
public:
    static bool SafeSave(const Player& player, const std::string& filename) {
        try {
            player.save(filename);

            return true;
        } catch (const std::exception& e) {
            std::cerr << "저장 실패: " << e.what() << std::endl;

            return false;
        }
    }

    static Player* SafeLoad(const std::string& filename) {
        try {
            Player loaded = Player::load(filename);

            return new Player(loaded);
        } catch (const FileNotFoundException& e) {
            std::cerr << "로드 실패: " << e.what() << std::endl;
            std::cerr << "새 게임을 시작합니다." << std::endl;
        } catch (const CorruptedSaveException& e) {
            std::cerr << "로드 실패: " << e.what() << std::endl;
            std::cerr << "백업 파일을 확인하세요." << std::endl;
        } catch (const InvalidStatException& e) {
            std::cerr << "로드 실패: " << e.what() << std::endl;
            std::cerr << "세이브 데이터가 손상되었습니다." << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "알 수 없는 오류: " << e.what() << std::endl;
        }

        return nullptr;
    }
};

int main() {
    {
        std::cout << "\n테스트 1: 정상 세이브/로드" << std::endl;

        Player player("홍길동", 10, 500, 1000);

        player.display();

        GameManager::SafeSave(player, "save1.sav");

        Player* loaded = GameManager::SafeLoad("save1.sav");

        if (loaded != nullptr) {
            loaded->display();

            delete loaded;
        }
    }

    {
        std::cout << "\n테스트 2: 존재하지 않는 파일" << std::endl;

        Player* loaded = GameManager::SafeLoad("없는파일.sav");

        if (loaded == nullptr) {
            // 무언가 하기
        }
    }

    {
        std::cout << "\n테스트 3: 손상된 세이브 파일" << std::endl;

        std::ofstream invalid("corrupt.sav");

        invalid << "이름만있음\n";
        invalid.close();

        Player* loaded = GameManager::SafeLoad("corrupt.sav");

        if (loaded == nullptr) {
            // 무언가 하기
        }
    }

    {
        std::cout << "\n테스트 4: 유효하지 않은 스탯 - 레벨 초과" << std::endl;

        try {
            Player invalid("해커", 999, 100, 0);
        } catch (const InvalidStatException& e) {
            std::cerr << "생성 실패: " << e.what() << std::endl;
        }
    }

    {
        std::cout << "\n테스트 5: 손상된 세이브 - 잘못된 레벨" << std::endl;

        std::ofstream invalid("badsave.sav");

        invalid << "치터\n";
        invalid << "999\n";
        invalid << "100\n";
        invalid << "0\n";
        invalid.close();

        Player* loaded = GameManager::SafeLoad("badsave.sav");

        if (loaded == nullptr) {
            // 무언가 하기
        }
    }

    return 0;
}
