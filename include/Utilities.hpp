#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <QString>
#include <QStringView>

namespace Utilities
{
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