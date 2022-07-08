import RPi.GPIO as GPIO

outputUpdate = 8
outputDiag = 10
outputResponseFlag = 12

inputUpdate = 16
inputDiagTemp = 18
inputDiagDirections = 22
inputDiagUltra = 24
inputDiagFlag = 26

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
GPIO.setup(outputUpdate, GPIO.OUT, initial=GPIO.HIGH)
GPIO.setup(outputDiag, GPIO.OUT, initial=GPIO.HIGH)
GPIO.setup(outputResponseFlag, GPIO.OUT, initial=GPIO.HIGH)

GPIO.setup(inputUpdate, GPIO.IN)
GPIO.setup(inputDiagTemp, GPIO.IN)
GPIO.setup(inputDiagDirections, GPIO.IN)
GPIO.setup(inputDiagUltra, GPIO.IN)
GPIO.setup(inputDiagFlag, GPIO.IN)


while True:
    if(GPIO.input(inputUpdate)):
        GPIO.output(outputUpdate,GPIO.LOW)
        GPIO.output(outputResponseFlag, GPIO.LOW)
    else:
        GPIO.output(outputUpdate, GPIO.HIGH)
        GPIO.output(outputResponseFlag, GPIO.LOW)
