#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>

// AI assistance: OpenAI ChatGPT.
// Prompt: "Provide a C++ worked implementation of CodeLab II
// Challenge 2 using file handling, random joke selection,
// user interaction and separate setup/punchline display."

struct Joke {
    std::string setup;
    std::string punchline;
};
// Load jokes from the supplied text file
std::vector<Joke> loadJokes(const std::string& filename) {
    std::vector<Joke> jokes;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Cannot open " << filename << "\n";
        return jokes;
    }
    std::string line;

    while (std::getline(file, line)) {
        size_t separator = line.find('?');

        if (separator == std::string::npos) {
            continue;
        }

        Joke joke;
        joke.setup = line.substr(0, separator + 1);
        joke.punchline = line.substr(separator + 1);

        if (!joke.punchline.empty()) {
            jokes.push_back(joke);
        }
    }

    return jokes;
}
// Select a random joke and reveal its punchline
void tellJoke(const std::vector<Joke>& jokes,
              std::mt19937& generator) {

    std::uniform_int_distribution<size_t> distribution(
        0, jokes.size() - 1
    );

    const Joke& joke = jokes[distribution(generator)];

    std::cout << "\nAlexa: " << joke.setup << "\n";
    std::cout << "Press ENTER to hear the punchline...";

    std::string response;
    std::getline(std::cin, response);

    std::cout << "Alexa: " << joke.punchline << "\n\n";
}
int main() {
    std::vector<Joke> jokes = loadJokes("randomJokes.txt");

    if (jokes.empty()) {
        std::cerr << "No jokes available. Check the file.\n";
        return 1;
    }
    std::random_device device;
    std::mt19937 generator(device());

    std::cout << "=================================\n";
    std::cout << "       ALEXA JOKE GENERATOR\n";
    std::cout << "=================================\n";
    std::cout << "Type: Alexa, tell me a joke\n";
    std::cout << "Type: quit to exit\n\n";

    std::string command;

    while (true) {
        std::cout << "You: ";

        if (!std::getline(std::cin, command)) {
            break;
        }

        if (command == "quit") {
            std::cout << "Alexa: Goodbye!\n";
            break;
        }
        if (command == "Alexa, tell me a joke") {
            tellJoke(jokes, generator);
        } else {
            std::cout << "Alexa: Command not recognised.\n";
            std::cout << "Try: Alexa, tell me a joke\n\n";
        }
    }
    return 0;
}