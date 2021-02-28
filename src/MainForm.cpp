#include "MainForm.hpp"
#include "Utilities.hpp"

#include <QFrame>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSizeGrip>

#include <iostream>

MainForm::MainForm(QWidget* parent)
    : RoundedDialog(parent)
{
    QVBoxLayout* centralLayout = new QVBoxLayout();

    QHBoxLayout* timeFrameExitLayout = new QHBoxLayout();
    timeFrameExitLayout->setSpacing(1);

    timeFrameExitLayout->addStretch(1);
    timeFrameExitLayout->addWidget(this->createTimeFrameToggleWidget(), 0, Qt::AlignHCenter);
    timeFrameExitLayout->addSpacing(20);
    timeFrameExitLayout->addWidget(this->createExitWidget());
    timeFrameExitLayout->addSpacing(15);

    // Need to add this spacer item so we get a decent buffer between the top of the main window
    // and the time toggle.
    centralLayout->addSpacing(20);
    centralLayout->addLayout(timeFrameExitLayout);

    QSizeGrip* sizeGrip = new QSizeGrip(this);

    centralLayout->addWidget(sizeGrip, 0, Qt::AlignBottom | Qt::AlignRight);

    this->setLayout(centralLayout);
    this->setFixedWidth(350);
}

QWidget* MainForm::createExitWidget()
{
    QPushButton* exitButton = new QPushButton(this);
    exitButton->setStyleSheet("QPushButton { background-color: " + Utilities::Constants::getBackgroundColor().name() +
                              "; image: url(resources/exit_button_light.svg); border-style: outset;} \
                               QPushButton:pressed {background-color: " +
                              Utilities::Constants::getBackgroundColor().name() +
                              "; image: url(resources/exit_button_light.svg); border-style: outset;}");
    exitButton->setFixedSize(28, 28);

    QObject::connect(exitButton, &QPushButton::clicked, this, &QDialog::close);

    return exitButton;
}

QWidget* MainForm::createTimeFrameToggleWidget()
{
    const QString fontSize = "13";

    const QString buttonBodySS = "";

    QFrame* background = new QFrame(this);
    background->setStyleSheet("QFrame {background-color: " + Utilities::Constants::getBaseColor().name() + "; border-radius: 12px;}");
    background->setFixedWidth(200);
    background->setFixedHeight(24);

    QPushButton* buttonTime = new QPushButton("Time", background);
    buttonTime->setStyleSheet("QPushButton {color: white; background-color: " + Utilities::Constants::getBaseColor().name() +
                              "; font-size: " + fontSize + "px; border-style: outset;} \
                               QPushButton:pressed {background-color: " +
                              Utilities::Constants::getBaseColor().name() + "; border-style: outset;}");
    buttonTime->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    buttonTime->setFixedHeight(17);
    buttonTime->setFlat(true);

    QFrame* seperator = new QFrame(background);
    seperator->setFrameShape(QFrame::Shape::VLine);
    seperator->setStyleSheet("QFrame {background-color: " + Utilities::Constants::getHighlightColor().name() + ";}");
    seperator->setFixedHeight(24);

    QPushButton* buttonFrames = new QPushButton("Frame", background);
    buttonFrames->setStyleSheet("QPushButton {color: " + Utilities::Constants::getHighlightColor().name() + "; background-color: " +
                                Utilities::Constants::getBaseColor().name() + "; font-size: " + fontSize + "px; border-style: outset;} \
                                 QPushButton:pressed {background-color: " +
                                Utilities::Constants::getBaseColor().name() + "; border-style: outset;}");
    buttonFrames->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    buttonFrames->setFixedHeight(17);
    buttonFrames->setFlat(true);

    // Lambda to update the button stylesheets depending on which on is selected/clicked.
    auto updateButtonColors = [buttonTime, buttonFrames](bool isTimeSelected) {
        QString tag = "color: ";

        QString timeColor = isTimeSelected ? "white" : Utilities::Constants::getHighlightColor().name();
        QString frameColor = isTimeSelected ? Utilities::Constants::getHighlightColor().name() : "white";

        QString styleSheetTime = buttonTime->styleSheet();
        Utilities::Widgets::changeStyleSheetTag(styleSheetTime, tag, timeColor);
        buttonTime->setStyleSheet(styleSheetTime);

        QString styleSheetFrames = buttonFrames->styleSheet();
        Utilities::Widgets::changeStyleSheetTag(styleSheetFrames, tag, frameColor);
        buttonFrames->setStyleSheet(styleSheetFrames);
    };

    // Lambda that gets called on button presses. Update the button stylesheets then emit
    // the signal for subscribers to be notified of the selection.
    QObject::connect(buttonTime, &QPushButton::clicked, this, [this, updateButtonColors] {
        updateButtonColors(true);
        emit sigTimeSelected();
    });
    QObject::connect(buttonFrames, &QPushButton::clicked, this, [this, updateButtonColors] {
        updateButtonColors(false);
        emit sigFrameSelected();
    });

    // Content Margins must be zero or else there is too much padding and the words
    // start to get cut off.
    QHBoxLayout* backgroundLayout = new QHBoxLayout();
    backgroundLayout->setContentsMargins(0, 0, 0, 0);

    backgroundLayout->addStretch(1);
    backgroundLayout->addWidget(buttonTime);
    backgroundLayout->addStretch(1);
    backgroundLayout->addWidget(seperator);
    backgroundLayout->addStretch(1);
    backgroundLayout->addWidget(buttonFrames);
    backgroundLayout->addStretch(1);

    background->setLayout(backgroundLayout);

    return background;
}