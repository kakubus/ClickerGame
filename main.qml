import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15

ApplicationWindow {
    width: 1024; minimumWidth: 1024; maximumWidth: 1024;
    height: 786; minimumHeight: 786; maximumHeight: 1024;
    visible: true
    title: qsTr("GameClicker")

    Material.theme: Material.Light
    Material.accent: Material.Green


    Connections{
        target: CGEngine

       // onIsConnectedChanged:\
        function onChangePosition() {
            masterclick.x = CGEngine.getXPosition();
            masterclick.y = CGEngine.getYPosition();
        }

        function onUpdateTime(){
            masterclick.visible = true
            startButton.enabled = false
            texttime.text = qsTr("Time:\t")+CGEngine.getTimeGame()+qsTr("s");
           // timeprogress.value =
        }

        function onUpdateScore()
        {
            textscore.text = qsTr("Score:\t")+CGEngine.getScoreGame();

        }

        function onTimeProgressUpdate(){
            timeprogress.to = CGEngine.getTimeInterval();
            timeprogress.value = CGEngine.getRemainingTime();
        }

        function onShowDialog()
        {
            dialog.open();
            textheader.text = CGEngine.getDialogHeader();
            textscoreinfo.text = CGEngine.getDialogText();
            texthint.visible = false;

        }

        function onLevelUpdate()
        {
            textlevel.text = CGEngine.getLevel();
        }

        function onShortInfo()
        {
            texthint.text = CGEngine.getDialogText();
        }


    }



    header: ToolBar { // HEADER - START/STOP


        Material.background:  Material.Green
        Flow {
            padding: 5
            anchors.fill: parent
            ToolButton {
                id: startButton
                text: qsTr("Start")
                icon.name: "document-open"
                onClicked: {
                    startdialog.open();

                }
            }
            ToolButton { //temp - to do scroll and Quit.dialog not Qt.quit()
                text: qsTr("Game Ranking")
                icon.name: "document-open"
                onClicked: {
                    dialog.open();
                    dialog.width = 600;
                    dialog.height = 600;

                    textscoreinfo.font.pixelSize = 14;
                    textscoreinfo.textFormat = Text.RichText;
                    textheader.text = "Game ranking";
                    textscoreinfo.text = CGEngine.showRanking();


                }
            }
            ToolButton {
                text: qsTr("Quit")
                icon.name: "document-open"
                onClicked: {
                    dialog.open();
                    textscoreinfo.text = qsTr("Your score:\t")+CGEngine.getScoreGame() +"points\n"+ qsTr("Play time:\t")+CGEngine.getTimeGame()+qsTr("s");
                    CGEngine.stopGame();

                }
            }
        }
    }

    GridLayout{
        columns: 1
        anchors.fill: parent

        Pane{

           anchors.fill: parent
           // anchors.centerIn: parent
            Material.foreground: "#EEEEEE"
            Material.background: "#404040"

            ColumnLayout{
                anchors.centerIn: parent
               // spacing: 10
                Column{ // Game info

                    Rectangle{
                        id: rectangle_game_stats
                        color: "gray"
                        width: 800
                        height: 35
                        border.width: 1
                        border.color: "#202020"


                        RowLayout{
                            anchors.fill: parent
                            anchors.centerIn: parent

                            Row{
                                Label{
                                    id: textlevel
                                    text: "Level: 1"
                                     color: "#EEEEEE"
                                     font.pixelSize: 16
                                     font.family: "Bahnschrift"
                                     leftPadding: 20
                                     bottomPadding: 5

                                }
                            }

                            Row{
                                Label{
                                    id: textscore
                                    text: "Score: 0"
                                     color: "#EEEEEE"
                                     font.pixelSize: 16
                                     font.family: "Bahnschrift"
                                     bottomPadding: 5
                                }
                            }

                            Row{
                                Label{
                                    id: texttime
                                   // enabled: false
                                    text: "Not started!"
                                    color: "#EEEEEE"
                                    font.pixelSize: 16
                                    font.family: "Bahnschrift"
                                    bottomPadding: 5
                                }
                            }
                        }

                        ProgressBar{
                            id: timeprogress
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: parent.width - 2
                            anchors.top: parent.bottom
                            from: 0
                            to: 100
                            value: 0
                        }

                    }
                }

                Column{ // Main window for clicker

                    anchors.centerIn: parent

                    Rectangle{
                        id: rectangle_main_clicker
                         border.width: 1
                         border.color: "#202020"
                         color: "gray"
                         width: 800; height: 600

                        Button{
                            id: masterclick
                            text: "1"
                            width: 25; height: 40
                            x: 0; y: 0
                            visible: false

                            icon.source: "icons8-user-100.png"
                            padding: 0
                            icon.height: 50
                            icon.width: 50

                            icon.color: "transparent"

                            onClicked:{
                                CGEngine.clicked();
                            }
                        }
                    }
                }
                Column{ // Game hints

                    Rectangle{
                        id: rectangle_hints
                        color: "#404040"
                        width: 800
                        height: 35
                        border.width: 1
                        border.color: "#666666"


                        RowLayout{
                            anchors.fill: parent
                            anchors.centerIn: parent


                            Row{
                                Label{

                                    id: textinfo
                                    text: "Info:"
                                     color: "#EEEEEE"
                                     font.pixelSize: 20
                                     font.family: "Bahnschrift"
                                     leftPadding: 20
                                     bottomPadding: 5

                                }
                            }
                            Row{
                                anchors.centerIn: parent
                                Label{
                                    id: texthint
                                    text: "Please start the game!"
                                     color: "#EEEEEE"
                                     font.pixelSize: 20
                                     font.family: "Bahnschrift"
                                     bottomPadding: 5
                                     //leftPadding: 120
                                }
                            }

                        }
                    }
                }

            }


            Text{
                id: textshortinfo
                color: "#EEEEEE"
                text: "Level 1: 0 - 100\nLevel 2: 101-299\nLevel 3: 300-400\nWin: 400 pts"
            }
        }

    }

    footer: Pane{ //FOOTER - BOTTOM APP
          //  height: 25
            Material.background:  Material.Green

            Text{
                color: "#EEEEEE"
                anchors.centerIn: parent
               // verticalAlignment: parent.verticalCenter
               // anchors.left: parent.left
                text: qsTr("Made in Poland 2022 | JK")
            }

//            Text {
//                id: hintLabel
//                //anchors.margins: 5
//                verticalAlignment: parent.verticalCenter
//                anchors.right: parent.right
//                text: qsTr("<Timer>")
//            }


        }

    Dialog { //main dialog
        id: dialog
        modal: true
        standardButtons: Dialog.Ok

        width: 300; height: 250
        anchors.centerIn: parent

        onAccepted:{

            Qt.quit()
        }
        header: Rectangle{

            width: parent; height: 38
            color: "#404040"

            Text{
                id: textheader
                text: "Game summary"

                anchors{
                    top: parent.top
                    topMargin: 8
                    leftMargin: 8
                    fill: parent
                    centerIn: parent
                }
                color: "#EEEEEE"
                font.pixelSize: 16
            }

        }

        Text{
            id: textscoreinfo
            font.pixelSize: 20
            text: qsTr("Your score: ")+CGEngine.getScoreGame();
        }


    }

    Dialog { //dialog when game is started
        id: startdialog
        modal: true
        standardButtons: Dialog.Ok

        width: 300; height: 250
        anchors.centerIn: parent

        onAccepted:{
            CGEngine.timeGameScheduler();
            CGEngine.setNewCoordinates(false);
           // CGEngine.setNickname(TextInput.text);
            texttime.text = "Let's go!"
            texthint.text = "Hit icon"
        }

        header: Rectangle{

            width: parent; height: 38
            color: "#404040"

            Text{
                id: starttextheader
                text: "Set your nickname.."

                anchors{
                    top: parent.top
                    topMargin: 8
                    leftMargin: 8
                    fill: parent
                    centerIn: parent
                }
                color: "#EEEEEE"
                font.pixelSize: 16
            }

        }
        RowLayout{
            anchors.fill: parent
            Row{
                Text{
                    id: starttextinfo
                    font.pixelSize: 16
                    text: qsTr("Enter your nick: ");
                }
            }
            Row{
                Rectangle{
                    border.width: 1
                    border.color: "#73706D"
                    width: 120
                    height: 35
                    TextInput{
                        id: nickname
                        width: parent.width
                        height: parent.height
                        anchors.fill: parent
                        font.pixelSize: 16
                        maximumLength: 10
                        horizontalAlignment: TextInput.AlignHCenter
                        verticalAlignment: TextInput.AlignVCenter
                       // onTextChanged:
                      //  onAccepted: CGEngine.setNickname(text);
                        onEditingFinished: CGEngine.setNickname(text);

                    }
                }
            }
        }







    }
}
