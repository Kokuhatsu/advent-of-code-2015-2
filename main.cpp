#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>

int main() {
    const auto input_file_path = std::filesystem::path(__FILE__).remove_filename() / "input.txt";
    auto input_file = std::fstream(input_file_path, std::ios_base::in);

    assert(input_file.is_open());

    std::uint32_t total_paper_required{0};
    while(input_file.eof() == false) {
        std::string package_dimensions{};
        input_file >> package_dimensions;

        std::stringstream dimensions_stream{package_dimensions};
        std::array<std::uint32_t, 3> dimensions{0, 0, 0};
        auto dimensions_iterator = dimensions.begin();

        for(std::string dimension; std::getline(dimensions_stream, dimension, 'x');) {
            *(dimensions_iterator++) = static_cast<std::uint32_t>(std::stoi(dimension));
        }

        enum dimension_name {
            length_dimension,
            width_dimension,
            height_dimension
        };

        const auto& length = dimensions[length_dimension];
        const auto& width = dimensions[width_dimension];
        const auto& height = dimensions[height_dimension];

        std::array<std::uint32_t, 3> wall_area{length * width,
                                               length * height,
                                               width * height};

        const auto smalest_area = *(std::min_element(wall_area.cbegin(), wall_area.cend()));
        const auto total_area = 2 * std::accumulate(wall_area.cbegin(), wall_area.cend(), 0, std::plus<std::uint32_t>());

        total_paper_required += smalest_area + total_area;
    }

    std::cout << "Required paper: " << total_paper_required << std::endl;

    return 0;
}
