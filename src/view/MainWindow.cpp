#include "../../include/view/MainWindow.hpp"
#include <QWidget>
#include <QMessageBox>
#include <QTimer>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), controller_()
{
    setupUI();
    updateUI();
}

MainWindow::~MainWindow()
{
    // Qt handles cleanup via parent-child relationship
}

void MainWindow::setupUI()
{
    setWindowTitle(" Higher or Lower");
    setMinimumSize(500, 500);

    // Central widget and main layout
    QWidget *centralWidget = new QWidget(this); // canvas
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(40, 40, 40, 40);

    mainLayout->addStretch();

    // Current card display
    currentCardLabel_ = new QLabel("🃏", this);
    QFont cardFont = currentCardLabel_->font();
    cardFont.setPointSize(72);
    currentCardLabel_->setFont(cardFont);
    currentCardLabel_->setAlignment(Qt::AlignCenter);
    currentCardLabel_->setStyleSheet("QLabel { background-color: white; padding: 40px; border-radius: 15px; border: 3px solid #333; }");
    mainLayout->addWidget(currentCardLabel_);

    // Active player label (make it prominent)
    activePlayerLabel_ = new QLabel("▶ PLAYER 1 ◀", this);
    activePlayerLabel_->setAlignment(Qt::AlignCenter);
    QFont playerFont = activePlayerLabel_->font();
    playerFont.setPointSize(20);
    playerFont.setBold(true);
    activePlayerLabel_->setFont(playerFont);
    activePlayerLabel_->setStyleSheet("QLabel { color: white; background-color: #2196F3; padding: 15px; border-radius: 10px; }");
    mainLayout->addWidget(activePlayerLabel_);

    // Score display
    scoreLabel_ = new QLabel("Player 1: 0  |  Player 2: 0", this);
    scoreLabel_->setAlignment(Qt::AlignCenter);
    QFont scoreFont = scoreLabel_->font();
    scoreFont.setPointSize(16);
    scoreFont.setBold(true);
    scoreLabel_->setFont(scoreFont);
    mainLayout->addWidget(scoreLabel_);

    // Message/feedback label
    messageLabel_ = new QLabel("Make your guess!", this);
    messageLabel_->setAlignment(Qt::AlignCenter);
    messageLabel_->setWordWrap(true);
    messageLabel_->setStyleSheet("QLabel { color: #0066cc; }");
    mainLayout->addWidget(messageLabel_);

    // Buttons layout
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(15);

    higherButton_ = new QPushButton("⬆ HIGHER", this);
    higherButton_->setMinimumHeight(70);
    QFont buttonFont = higherButton_->font();
    buttonFont.setPointSize(18);
    buttonFont.setBold(true);
    higherButton_->setFont(buttonFont);
    higherButton_->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; border-radius: 10px; border: none; }"
                                 "QPushButton:hover { background-color: #45a049; }"
                                 "QPushButton:pressed { background-color: #3d8b40; }");
    connect(higherButton_, &QPushButton::clicked, this, &MainWindow::onHigherButtonClicked);

    lowerButton_ = new QPushButton("⬇ LOWER", this);
    lowerButton_->setMinimumHeight(70);
    lowerButton_->setFont(buttonFont);
    lowerButton_->setStyleSheet("QPushButton { background-color: #f44336; color: white; border-radius: 10px; border: none; }"
                                "QPushButton:hover { background-color: #da190b; }"
                                "QPushButton:pressed { background-color: #c41408; }");
    connect(lowerButton_, &QPushButton::clicked, this, &MainWindow::onLowerButtonClicked);

    buttonLayout->addWidget(higherButton_);
    buttonLayout->addWidget(lowerButton_);
    mainLayout->addLayout(buttonLayout);

    // Reset button
    resetButton_ = new QPushButton("Reset", this);
    resetButton_->setMinimumHeight(40);
    QFont resetFont = resetButton_->font();
    resetFont.setPointSize(12);
    resetButton_->setFont(resetFont);
    resetButton_->setStyleSheet("QPushButton { background-color: #888; color: white; border-radius: 8px; border: none; }"
                                "QPushButton:hover { background-color: #666; }");
    connect(resetButton_, &QPushButton::clicked, this, &MainWindow::onResetButtonClicked);
    mainLayout->addWidget(resetButton_);

    // How to Play button
    howToPlayButton_ = new QPushButton("How to Play", this);
    howToPlayButton_->setMinimumHeight(40);
    howToPlayButton_->setFont(resetFont);
    howToPlayButton_->setStyleSheet("QPushButton { background-color: #2196F3; color: white; border-radius: 8px; border: none; }"
                                    "QPushButton:hover { background-color: #1976D2; }");
    connect(howToPlayButton_, &QPushButton::clicked, this, &MainWindow::onHowToPlayClicked);
    mainLayout->addWidget(howToPlayButton_);

    mainLayout->addStretch();

    setCentralWidget(centralWidget);
}

void MainWindow::onHigherButtonClicked()
{
    controller_.makeGuess(true);
    updateUI();
    showFeedback(); // Call AFTER updateUI so it doesn't get overwritten
}

void MainWindow::onLowerButtonClicked()
{
    controller_.makeGuess(false);
    updateUI();
    showFeedback(); // Call AFTER updateUI so it doesn't get overwritten
}

void MainWindow::onResetButtonClicked()
{
    controller_.resetGame();
    updateUI();
    messageLabel_->setText("Game reset! Make your guess.");
}

void MainWindow::onHowToPlayClicked()
{
    QString instructions =
        "<h2 style='color: #2196F3;'>Higher or Lower - How to Play</h2>"
        "<p><b>Objective:</b> Guess whether the next card will be higher or lower than the current card.</p>"

        "<h3>Game Rules:</h3>"
        "<ul>"
        "<li>Two players take turns guessing</li>"
        "<li>Correct guess = 1 point</li>"
        "<li>Cards are ranked: 2 (lowest) to Ace (highest)</li>"
        "<li>Same suit: Clubs < Diamonds < Hearts < Spades</li>"
        "</ul>"

        "<h3>Joker Effects:</h3>"
        "<ul>"
        "<li><b>♣️ Clover Joker:</b> Wild Card - Automatic win!</li>"
        "<li><b>♦️ Diamond Joker:</b> Reverse - Wrong guess = win!</li>"
        "<li><b>♥️ Heart Joker:</b> Double points (2 points if correct)</li>"
        "<li><b>♠️ Spade Joker:</b> Swaps both players' scores!</li>"
        "</ul>"

        "<h3>Tips:</h3>"
        "<ul>"
        "<li>Watch for jokers - they can change the game!</li>"
        "<li>Use the peek ability wisely</li>"
        "<li>Middle cards (6-9) are hardest to predict</li>"
        "</ul>"

        "<p style='text-align: center; color: #666;'><i>Good luck and have fun!</i></p>";

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("How to Play");
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText(instructions);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

void MainWindow::showFeedback()
{
    bool correct = controller_.wasLastGuessCorrect();
    int points = controller_.getLastPointsAwarded();

    // Play system sound
    if (correct)
    {
        QApplication::beep(); // System beep for correct
    }

    // Show feedback message
    QString feedbackMsg;
    QString feedbackColor;

    if (points == 2)
    {
        feedbackMsg = "CORRECT! +2 points (Heart Joker bonus!)";
        feedbackColor = "#4CAF50"; // Green
    }
    else if (points == 1)
    {
        feedbackMsg = "CORRECT! +1 point";
        feedbackColor = "#4CAF50"; // Green
    }
    else
    {
        feedbackMsg = "WRONG! No points";
        feedbackColor = "#f44336"; // Red
    }

    messageLabel_->setText(feedbackMsg);
    messageLabel_->setStyleSheet(QString("QLabel { color: %1; font-weight: bold; font-size: 14pt; }").arg(feedbackColor));

    // Reset message after 2 seconds
    QTimer::singleShot(2000, this, [this]()
                       {
        messageLabel_->setStyleSheet("QLabel { color: #0066cc; font-weight: normal; font-size: 10pt; }");
        messageLabel_->setText("Make your guess!"); });
}

void MainWindow::updateUI()
{
    // Update current card
    std::string cardStr = controller_.getCurrentCardString();
    currentCardLabel_->setText(formatCardForDisplay(cardStr));

    // Update scores
    int p1Score = controller_.getPlayerScore(0);
    int p2Score = controller_.getPlayerScore(1);
    scoreLabel_->setText(QString("Player 1: %1  |  Player 2: %2").arg(p1Score).arg(p2Score));

    // Update active player with prominent display
    int activePlayer = controller_.getActivePlayerIndex();
    QString playerText = QString("▶ PLAYER %1 ◀").arg(activePlayer + 1);

    // Change color based on player
    QString bgColor = (activePlayer == 0) ? "#2196F3" : "#FF9800";
    activePlayerLabel_->setStyleSheet(QString("QLabel { color: white; background-color: %1; padding: 15px; border-radius: 10px; }").arg(bgColor));
    activePlayerLabel_->setText(playerText);

    // Reset message to default
    messageLabel_->setStyleSheet("QLabel { color: #0066cc; }");
    messageLabel_->setText("Make your guess!");
}

QString MainWindow::formatCardForDisplay(const std::string &cardStr) const
{
    QString qCardStr = QString::fromStdString(cardStr);

    // Handle Jokers with their effects
    if (qCardStr == "Joker")
    {
        // This shouldn't happen anymore since we get the joker with suit
        return "🃏 Joker";
    }

    // Replace suit names with emoji symbols
    qCardStr.replace("Clovers", "♣️");
    qCardStr.replace("Diamonds", "♦️");
    qCardStr.replace("Hearts", "♥️");
    qCardStr.replace("Spades", "♠️");

    return qCardStr;
}
