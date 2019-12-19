import QtQuick 2.0

Rectangle {
    width: 450; height: 450; color: "#313131"; border.width: 0
    

    Grid {
        x: 25; y: 25
        rows: 3; columns: 3; spacing: 0
        
        Repeater { model: 9
            
            Rectangle {
                id: square
                objectName: "square"
                width: 120; height: 120
                opacity: sqMouseArea.containsPress ? 0.6 : 1.0
                color: "#313131";
                border.width: 0
                border.color: "white"
                
                Image { 
                    id: img
                    width:64; height:64
                    anchors.centerIn: parent
                }

                MouseArea {
                    id: sqMouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    acceptedButtons: Qt.LeftButton
                    onClicked: {
                        img.source = W.getIconPath()
                        W.squareClicked(index);
                        sqMouseArea.enabled = false
                    }
                }
                
                Connections {
                    target: W
                    onGameOver: {
                        sqMouseArea.enabled = false
                    }
                    onGameReset: {
                        sqMouseArea.enabled = true
                        img.source = ""
                    }
                }
            }
        }
    }
    

    Rectangle {
        x: 145; y: 25
        width: 1; 
        height: 360; 
        color: "white"; 
        border.width: 1
    }
    
    Rectangle {
        x: 265; y: 25
        width: 1; 
        height: 360; 
        color: "white"; 
        border.width: 1
    }
    
    Rectangle {
        x: 25; y: 145
        width: 360; 
        height: 1; 
        color: "white"; 
        border.width: 1
    }
    
    Rectangle {
        x: 25; y: 265
        width: 360; 
        height: 1; 
        color: "white"; 
        border.width: 1
    }
}

