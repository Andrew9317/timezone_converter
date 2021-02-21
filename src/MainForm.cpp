#include "MainForm.hpp"
#include "Utilities.hpp"

#include <QFrame>
#include <QPushButton>
#include <QHBoxLayout>

#include <iostream>

MainForm::MainForm(QWidget* parent)
:QMainWindow(parent)
{
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* centralLayout = new QVBoxLayout();

    QHBoxLayout* timeFrameToggleLayout = new QHBoxLayout();
    timeFrameToggleLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Fixed));
    timeFrameToggleLayout->addWidget(this->createTimeFrameToggleWidget());
    timeFrameToggleLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Fixed));

    centralLayout->addLayout(timeFrameToggleLayout);

    centralWidget->setLayout(centralLayout);
    this->setCentralWidget(centralWidget);
}

QWidget* MainForm::createTimeFrameToggleWidget()
{
    const QString fontSize = "13";
    const QString baseHexColor = "#2E2828";
    const QString secondaryHexColor = "#707070";

    const QString buttonBodySS = "";

    QFrame* background = new QFrame(this);
    background->setStyleSheet("QFrame {background-color: " + baseHexColor + "; border-radius: 12px;}");
    background->setFixedWidth(200);
    background->setFixedHeight(24);

    QPushButton* buttonTime = new QPushButton("Time", background);
    buttonTime->setStyleSheet("QPushButton {color: white; background-color: " + baseHexColor + "; font-size: " + fontSize + "px;} \
                               QPushButton:pressed {background-color: " + baseHexColor + "; border-style: outset;}");
    buttonTime->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    buttonTime->setFixedHeight(17);
    buttonTime->setFlat(true);

    QFrame* seperator = new QFrame(background);
    seperator->setFrameShape(QFrame::Shape::VLine);
    seperator->setStyleSheet("QFrame {background-color: " + secondaryHexColor + ";}");
    seperator->setFixedHeight(24);

    QPushButton* buttonFrames = new QPushButton("Frame", background);
    buttonFrames->setStyleSheet("QPushButton {color: " + secondaryHexColor + "; background-color: " + baseHexColor + "; font-size: " + fontSize + "px;} \
                                 QPushButton:pressed {background-color: " + baseHexColor + "; border-style: outset;}");
    buttonFrames->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    buttonFrames->setFixedHeight(17);
    buttonFrames->setFlat(true);

    //Lambda to update the button stylesheets depending on which on is selected/clicked.
    auto updateButtonColors = [buttonTime, buttonFrames, secondaryHexColor](bool isTimeSelected){
        QString tag = "color: ";
        
        QString timeColor = isTimeSelected ? "white" : secondaryHexColor;
        QString frameColor = isTimeSelected ? secondaryHexColor : "white";

        QString styleSheetTime = buttonTime->styleSheet();
        Utilities::Widgets::changeStyleSheetTag(styleSheetTime, tag, timeColor);
        buttonTime->setStyleSheet(styleSheetTime);

        QString styleSheetFrames = buttonFrames->styleSheet();
        Utilities::Widgets::changeStyleSheetTag(styleSheetFrames, tag, frameColor);
        buttonFrames->setStyleSheet(styleSheetFrames);
    };

    //Lambda that gets called on button presses. Update the button stylesheets then emit
    //the signal for subscribers to be notified of the selection.
    QObject::connect(buttonTime, &QPushButton::clicked, this, [this, updateButtonColors]{
        updateButtonColors(true);
        emit sigTimeSelected();
    });
    QObject::connect(buttonFrames, &QPushButton::clicked, this, [this, updateButtonColors]{
        updateButtonColors(false);
        emit sigFrameSelected();
    });

    //Content Margins must be zero or else there is too much padding and the words
    //start to get cut off.
    QHBoxLayout* backgroundLayout = new QHBoxLayout();
    backgroundLayout->setContentsMargins(0, 0, 0, 0);

    backgroundLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Fixed));
    backgroundLayout->addWidget(buttonTime);
    backgroundLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Fixed));
    backgroundLayout->addWidget(seperator);
    backgroundLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Fixed));
    backgroundLayout->addWidget(buttonFrames);
    backgroundLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Fixed));

    background->setLayout(backgroundLayout);

    return background;
}