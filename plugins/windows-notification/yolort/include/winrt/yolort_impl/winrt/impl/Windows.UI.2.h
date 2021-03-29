// C++/WinRT v2.0.190620.2

// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#ifndef WINRT_Windows_UI_2_H
#define WINRT_Windows_UI_2_H
#include "Windows.UI.1.h"
namespace winrt::Windows::UI
{
    struct Color
    {
        uint8_t A;
        uint8_t R;
        uint8_t G;
        uint8_t B;
    };
    inline bool operator==(Color const& left, Color const& right) noexcept
    {
        return left.A == right.A && left.R == right.R && left.G == right.G && left.B == right.B;
    }
    inline bool operator!=(Color const& left, Color const& right) noexcept
    {
        return !(left == right);
    }
    struct __declspec(empty_bases) ColorHelper : Windows::UI::IColorHelper
    {
        ColorHelper(std::nullptr_t) noexcept {}
        ColorHelper(void* ptr, take_ownership_from_abi_t) noexcept : Windows::UI::IColorHelper(ptr, take_ownership_from_abi) {}
        static auto FromArgb(uint8_t a, uint8_t r, uint8_t g, uint8_t b);
        static auto ToDisplayName(Windows::UI::Color const& color);
    };
    struct __declspec(empty_bases) Colors : Windows::UI::IColors
    {
        Colors(std::nullptr_t) noexcept {}
        Colors(void* ptr, take_ownership_from_abi_t) noexcept : Windows::UI::IColors(ptr, take_ownership_from_abi) {}
        [[nodiscard]] static auto AliceBlue();
        [[nodiscard]] static auto AntiqueWhite();
        [[nodiscard]] static auto Aqua();
        [[nodiscard]] static auto Aquamarine();
        [[nodiscard]] static auto Azure();
        [[nodiscard]] static auto Beige();
        [[nodiscard]] static auto Bisque();
        [[nodiscard]] static auto Black();
        [[nodiscard]] static auto BlanchedAlmond();
        [[nodiscard]] static auto Blue();
        [[nodiscard]] static auto BlueViolet();
        [[nodiscard]] static auto Brown();
        [[nodiscard]] static auto BurlyWood();
        [[nodiscard]] static auto CadetBlue();
        [[nodiscard]] static auto Chartreuse();
        [[nodiscard]] static auto Chocolate();
        [[nodiscard]] static auto Coral();
        [[nodiscard]] static auto CornflowerBlue();
        [[nodiscard]] static auto Cornsilk();
        [[nodiscard]] static auto Crimson();
        [[nodiscard]] static auto Cyan();
        [[nodiscard]] static auto DarkBlue();
        [[nodiscard]] static auto DarkCyan();
        [[nodiscard]] static auto DarkGoldenrod();
        [[nodiscard]] static auto DarkGray();
        [[nodiscard]] static auto DarkGreen();
        [[nodiscard]] static auto DarkKhaki();
        [[nodiscard]] static auto DarkMagenta();
        [[nodiscard]] static auto DarkOliveGreen();
        [[nodiscard]] static auto DarkOrange();
        [[nodiscard]] static auto DarkOrchid();
        [[nodiscard]] static auto DarkRed();
        [[nodiscard]] static auto DarkSalmon();
        [[nodiscard]] static auto DarkSeaGreen();
        [[nodiscard]] static auto DarkSlateBlue();
        [[nodiscard]] static auto DarkSlateGray();
        [[nodiscard]] static auto DarkTurquoise();
        [[nodiscard]] static auto DarkViolet();
        [[nodiscard]] static auto DeepPink();
        [[nodiscard]] static auto DeepSkyBlue();
        [[nodiscard]] static auto DimGray();
        [[nodiscard]] static auto DodgerBlue();
        [[nodiscard]] static auto Firebrick();
        [[nodiscard]] static auto FloralWhite();
        [[nodiscard]] static auto ForestGreen();
        [[nodiscard]] static auto Fuchsia();
        [[nodiscard]] static auto Gainsboro();
        [[nodiscard]] static auto GhostWhite();
        [[nodiscard]] static auto Gold();
        [[nodiscard]] static auto Goldenrod();
        [[nodiscard]] static auto Gray();
        [[nodiscard]] static auto Green();
        [[nodiscard]] static auto GreenYellow();
        [[nodiscard]] static auto Honeydew();
        [[nodiscard]] static auto HotPink();
        [[nodiscard]] static auto IndianRed();
        [[nodiscard]] static auto Indigo();
        [[nodiscard]] static auto Ivory();
        [[nodiscard]] static auto Khaki();
        [[nodiscard]] static auto Lavender();
        [[nodiscard]] static auto LavenderBlush();
        [[nodiscard]] static auto LawnGreen();
        [[nodiscard]] static auto LemonChiffon();
        [[nodiscard]] static auto LightBlue();
        [[nodiscard]] static auto LightCoral();
        [[nodiscard]] static auto LightCyan();
        [[nodiscard]] static auto LightGoldenrodYellow();
        [[nodiscard]] static auto LightGreen();
        [[nodiscard]] static auto LightGray();
        [[nodiscard]] static auto LightPink();
        [[nodiscard]] static auto LightSalmon();
        [[nodiscard]] static auto LightSeaGreen();
        [[nodiscard]] static auto LightSkyBlue();
        [[nodiscard]] static auto LightSlateGray();
        [[nodiscard]] static auto LightSteelBlue();
        [[nodiscard]] static auto LightYellow();
        [[nodiscard]] static auto Lime();
        [[nodiscard]] static auto LimeGreen();
        [[nodiscard]] static auto Linen();
        [[nodiscard]] static auto Magenta();
        [[nodiscard]] static auto Maroon();
        [[nodiscard]] static auto MediumAquamarine();
        [[nodiscard]] static auto MediumBlue();
        [[nodiscard]] static auto MediumOrchid();
        [[nodiscard]] static auto MediumPurple();
        [[nodiscard]] static auto MediumSeaGreen();
        [[nodiscard]] static auto MediumSlateBlue();
        [[nodiscard]] static auto MediumSpringGreen();
        [[nodiscard]] static auto MediumTurquoise();
        [[nodiscard]] static auto MediumVioletRed();
        [[nodiscard]] static auto MidnightBlue();
        [[nodiscard]] static auto MintCream();
        [[nodiscard]] static auto MistyRose();
        [[nodiscard]] static auto Moccasin();
        [[nodiscard]] static auto NavajoWhite();
        [[nodiscard]] static auto Navy();
        [[nodiscard]] static auto OldLace();
        [[nodiscard]] static auto Olive();
        [[nodiscard]] static auto OliveDrab();
        [[nodiscard]] static auto Orange();
        [[nodiscard]] static auto OrangeRed();
        [[nodiscard]] static auto Orchid();
        [[nodiscard]] static auto PaleGoldenrod();
        [[nodiscard]] static auto PaleGreen();
        [[nodiscard]] static auto PaleTurquoise();
        [[nodiscard]] static auto PaleVioletRed();
        [[nodiscard]] static auto PapayaWhip();
        [[nodiscard]] static auto PeachPuff();
        [[nodiscard]] static auto Peru();
        [[nodiscard]] static auto Pink();
        [[nodiscard]] static auto Plum();
        [[nodiscard]] static auto PowderBlue();
        [[nodiscard]] static auto Purple();
        [[nodiscard]] static auto Red();
        [[nodiscard]] static auto RosyBrown();
        [[nodiscard]] static auto RoyalBlue();
        [[nodiscard]] static auto SaddleBrown();
        [[nodiscard]] static auto Salmon();
        [[nodiscard]] static auto SandyBrown();
        [[nodiscard]] static auto SeaGreen();
        [[nodiscard]] static auto SeaShell();
        [[nodiscard]] static auto Sienna();
        [[nodiscard]] static auto Silver();
        [[nodiscard]] static auto SkyBlue();
        [[nodiscard]] static auto SlateBlue();
        [[nodiscard]] static auto SlateGray();
        [[nodiscard]] static auto Snow();
        [[nodiscard]] static auto SpringGreen();
        [[nodiscard]] static auto SteelBlue();
        [[nodiscard]] static auto Tan();
        [[nodiscard]] static auto Teal();
        [[nodiscard]] static auto Thistle();
        [[nodiscard]] static auto Tomato();
        [[nodiscard]] static auto Transparent();
        [[nodiscard]] static auto Turquoise();
        [[nodiscard]] static auto Violet();
        [[nodiscard]] static auto Wheat();
        [[nodiscard]] static auto White();
        [[nodiscard]] static auto WhiteSmoke();
        [[nodiscard]] static auto Yellow();
        [[nodiscard]] static auto YellowGreen();
    };
    struct __declspec(empty_bases) UIContentRoot : Windows::UI::IUIContentRoot
    {
        UIContentRoot(std::nullptr_t) noexcept {}
        UIContentRoot(void* ptr, take_ownership_from_abi_t) noexcept : Windows::UI::IUIContentRoot(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) UIContext : Windows::UI::IUIContext
    {
        UIContext(std::nullptr_t) noexcept {}
        UIContext(void* ptr, take_ownership_from_abi_t) noexcept : Windows::UI::IUIContext(ptr, take_ownership_from_abi) {}
    };
}
#endif
