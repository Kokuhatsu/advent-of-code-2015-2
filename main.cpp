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
    std::uint32_t total_ribbon_required{0};
    while(input_file.eof() == false) {
        std::string package_dimensions{};
        input_file >> package_dimensions;

        if(package_dimensions.empty())
            break;

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

        const auto dimensions_product = std::accumulate(dimensions.cbegin(), dimensions.cend(), 1, std::multiplies<std::uint32_t>());
        const auto dimensions_sum = std::accumulate(dimensions.cbegin(), dimensions.cend(), 0, std::plus<std::uint32_t>());
        const auto longest_dimension = *(std::max_element(dimensions.cbegin(), dimensions.cend()));
        const auto shortest_ribbon = (dimensions_sum - longest_dimension) * 2;

        total_paper_required += smalest_area + total_area;
        total_ribbon_required += dimensions_product + shortest_ribbon;
    }

    std::cout << "Required paper: " << total_paper_required << std::endl;
    std::cout << "Required ribbon: " << total_ribbon_required << std::endl;

    return 0;
}
