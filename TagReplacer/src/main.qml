import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3

import TagList 1.0

Window {
    id: mainwindow
    width: 480
    height: 640
    visible: true
    color: backgroundColor
    title: qsTr("Tag Replacer")

    property int leftPadding: 25
    property int rightPadding: 25
    property int topPadding: 10
    property int bottomPadding: 10

    property string redColor: "#C23A00"
    property string yellowColor: "#FFE896"
    property string whiteColor: "#FFFFFF"
    property string backgroundColor: "#ECECEC"

    Label {
        id: header_input
        text: qsTr("Input Text")
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        font.pixelSize: 12
        anchors.rightMargin: mainwindow.rightPadding
        anchors.leftMargin: mainwindow.leftPadding
        anchors.topMargin: mainwindow.topPadding
    }

    Frame {
        id: frame_input
        implicitHeight: 100
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: header_input.bottom
        anchors.rightMargin: mainwindow.rightPadding
        anchors.leftMargin: mainwindow.leftPadding
        anchors.topMargin: mainwindow.topPadding
        padding: 1

        Rectangle {
            anchors.fill: parent
            color: whiteColor

            ScrollView {
                id: scrollview_input
                anchors.fill: parent

                TextArea {
                    id: input
                    text: qsTr("")
                    anchors.fill: parent
                    onTextChanged: {

                        input_message.visible = true
                    }
                }
            }
        }
    }

    Text {
        id: input_message
        text: qsTr("Input text has changed. Please confirm and check for new tags.")
        height: confirm_button.height
        anchors.left: parent.left
        anchors.right: confirm_button.left
        anchors.top: frame_input.bottom
        anchors.leftMargin: mainwindow.leftPadding
        anchors.rightMargin: mainwindow.rightPadding
        anchors.topMargin: mainwindow.topPadding

        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.WordWrap
        color: redColor
        visible: false
    }

    Button {
        id: confirm_button
        text: qsTr("Confirm input to check for tags")
        anchors.right: parent.right
        anchors.top: frame_input.bottom
        anchors.rightMargin: mainwindow.rightPadding
        anchors.topMargin: mainwindow.topPadding
        anchors.bottomMargin: mainwindow.bottomPadding

        onClicked: {
            output_message.visible = true;
            input_message.visible = false;
            tagList.checkStringSlot(input.text);
        }
    }

    Label {
        id: header_table
        text: qsTr("Tag Replacements")
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: confirm_button.bottom
        font.pixelSize: 12
        anchors.rightMargin: mainwindow.rightPadding
        anchors.leftMargin: mainwindow.leftPadding
        anchors.topMargin: mainwindow.topPadding
    }

    Frame {
        id: tag_table
        implicitHeight: 200
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: header_table.bottom
        anchors.rightMargin: mainwindow.rightPadding
        anchors.leftMargin: mainwindow.leftPadding
        anchors.topMargin: mainwindow.topPadding
        padding: 1

        RowLayout {
            id: table_header
            implicitHeight: 25
            anchors.left: parent.left
            anchors.right: parent.right
            spacing: 0

            Rectangle {
                Layout.preferredWidth: 25
                implicitHeight: parent.implicitHeight
                border.color: "#BDBDBD"
                border.width: 1
                color: whiteColor
                Text {
                    anchors.fill: parent
                    anchors.margins: 5
                    text: qsTr("Id")
                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignVCenter
                }
            }

            Rectangle {
                Layout.preferredWidth: 75
                implicitHeight: parent.implicitHeight
                border.color: "#BDBDBD"
                border.width: 1
                color: whiteColor
                Text {
                    anchors.fill: parent
                    anchors.margins: 5
                    text: qsTr("Tag")
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }
            }

            Rectangle {
                Layout.fillWidth: true
                implicitHeight: parent.implicitHeight
                border.color: "#BDBDBD"
                border.width: 1
                color: whiteColor
                Text {
                    anchors.fill: parent
                    anchors.margins: 5
                    text: qsTr("Replacement")
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }

        ListView {
            id: listView
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: table_header.bottom
            anchors.bottom: parent.bottom
            clip: true
            spacing: 0

            model: TagListModel {
                list: tagList
            }

            delegate: RowLayout {
                implicitHeight: 35
                anchors.left: parent.left
                anchors.right: parent.right
                spacing: 0

                Rectangle {
                    Layout.preferredWidth: 25
                    implicitHeight: parent.implicitHeight
                    border.color: "#BDBDBD"
                    border.width: 1
                    color: !model.valid ? redColor : (model.escaping ? yellowColor : backgroundColor )
                    Text {
                        anchors.fill: parent
                        anchors.margins: 5
                        text: model.number
                        horizontalAlignment: Text.AlignRight
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                Rectangle {
                    Layout.preferredWidth: 75
                    implicitHeight: parent.implicitHeight
                    border.color: "#BDBDBD"
                    border.width: 1
                    color: !model.valid ? redColor : (model.escaping ? yellowColor : backgroundColor )
                    Text {
                        anchors.fill: parent
                        anchors.margins: 5
                        text: model.tagName
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                TextField {
                    text: model.description
                    implicitHeight: parent.implicitHeight
                    onEditingFinished: model.description = text
                    Layout.fillWidth: true
                    readOnly: model.escaping || !model.valid
                }
            }
        }
    }

    Text {
        id: output_message
        text: qsTr("Input text was updated. Please replace tags and confirm to update your output.")
        height: replacement_button.height
        anchors.left: parent.left
        anchors.right: replacement_button.left
        anchors.top: tag_table.bottom
        anchors.leftMargin: mainwindow.leftPadding
        anchors.rightMargin: mainwindow.rightPadding
        anchors.topMargin: mainwindow.topPadding

        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.WordWrap
        color: redColor
        visible: false
    }

    Button {
        id: replacement_button
        text: qsTr("Replace tags")
        anchors.right: parent.right
        anchors.top: tag_table.bottom
        anchors.rightMargin: mainwindow.rightPadding
        anchors.topMargin: mainwindow.topPadding

        onClicked: {
            output_message.visible = false;
            output.text = tagList.replaceSlot();
        }

    }

    Label {
        id: header_output
        text: qsTr("Output Text")
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: replacement_button.bottom
        font.pixelSize: 12
        anchors.rightMargin: mainwindow.rightPadding
        anchors.leftMargin: mainwindow.leftPadding
        anchors.topMargin: mainwindow.topPadding
    }

    Frame {
        id: frame_output
        implicitHeight: 100
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: header_output.bottom
        anchors.bottom: parent.bottom
        anchors.rightMargin: mainwindow.rightPadding
        anchors.leftMargin: mainwindow.leftPadding
        anchors.topMargin: mainwindow.topPadding
        anchors.bottomMargin: mainwindow.bottomPadding
        padding: 1

        Rectangle {
            anchors.fill: parent

            ScrollView {
                id: scrollview_output
                anchors.fill: parent

                TextArea {
                    id: output
                    readOnly: true
                    anchors.fill: parent
                }
            }
        }
    }
}
