# importing required packages
from PyQt5 import QtGui
import folium  # pip install folium
from PyQt5.QtWebEngineWidgets import QWebEngineView
from PyQt5.QtWidgets import QWidget, QPushButton, QVBoxLayout
import pathlib
import io
current_directory = str(pathlib.Path(__file__).parent.absolute())


# Define main window
class MainAPP_Map (QWidget):

    def __init__(self, parent=None):
        super(MainAPP_Map, self).__init__(parent)
        QWidget.__init__(self)
        self.window()

        # StyleSheet for UI
        self.setStyleSheet("""
            QWidget{
                color: silver;
                background-color: #302F2F;
                selection-background-color:#3d8ec9;
                selection-color: black;
                background-clip: border;
                border-image: none;
                outline: 0;
            }

            QWidget:item:hover{
                background-color: #78879b;
                color: black;
            }

            QWidget:item:selected{
                background-color: #3d8ec9;
            }

            QPushButton{
                color: silver;
                background-color: #302F2F;
                border-width: 2px;
                border-color: #4A4949;
                border-style: solid;
                border-radius: 4px;
            }

            QPushButton:disabled{
                background-color: #302F2F;
                border-width: 2px;
                border-color: #3A3939;
                border-style: solid;
                padding-top: 12px;
                padding-bottom: 12px;
                padding-left: 20px;
                padding-right: 20px;
                border-radius: 4px;
                color: #808080;
            }

            QPushButton:focus{
                background-color: #3d8ec9;
                color: white;
            }

            QPushButton:checked{
                background-color: #4A4949;
                border-color: #6A6969;
            }

            QPushButton:hover{
                border: 2px solid #78879b;
                color: silver;
            }


            QPushButton:pressed{
                background-color: #484846;
            }
        """)

        layout = QVBoxLayout()
        self.setLayout(layout)

        coordinate = (31.2460617, 29.9667378)
        m = folium.Map(
            zoom_start=20,
            location=coordinate
        )

        folium.Marker(coordinate, popup='Current Location').add_to(m)
        folium.TileLayer('cartodbpositron').add_to(m)

        # save map data to data object
        data = io.BytesIO()
        m.save(data, close_file=False)

        webView = QWebEngineView()
        webView.setHtml(data.getvalue().decode())
        layout.addWidget(webView)

        self.initUI()

    def initUI(self):
        button = QPushButton('Back', self)
        button.move(25, 430)
        button.clicked.connect(self.Handle_Exit)

    # Window Size, Title and Icon
    def window(self):
        self.setWindowTitle("Maps")
        self.setFixedSize(800, 480)
        self.setWindowIcon(QtGui.QIcon(
            current_directory + '/../Images/icon.png'))

    def Handle_Exit(self):
        self.close()
