#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <QColor>
#include <QString>
#include <QStringView>

namespace Utilities
{
    namespace Constants
    {

        enum class Theme
        {
            DARK,
            LIGHT
        };

        Theme currentTheme = Theme::DARK;

        QColor getBaseColor() { return (currentTheme == Theme::DARK) ? QColor("#2E2828") : QColor("#D6D6D6"); }
        QColor getHighlightColor() { return QColor("#707070"); }
        QColor getBackgroundColor() { return (currentTheme == Theme::DARK) ? QColor("#535050") : QColor("#F3F2F2"); }

    } // namespace Constants
    namespace Widgets
    {
        void changeStyleSheetTag(QString& styleSheet, QStringView tag, QStringView value)
        {
            int tagIndex = styleSheet.indexOf(tag);
            int tagSemiColonIndex = styleSheet.indexOf(';', tagIndex);

            int tagValueIndex = tagIndex + tag.size();
            int tagValueSize = tagSemiColonIndex - tagValueIndex;
            styleSheet.remove(tagValueIndex, tagValueSize);
            styleSheet.insert(tagValueIndex, value);
        }
    } // namespace Widgets
} // namespace Utilities

#endif