from selenium import webdriver
import unittest, time
import os

if __name__ == '__main__':
	print("Please enter the question number you want to configure(1000~4999):")
	prob_num=int(input())
	prob_num=str(prob_num)
	url='https://darkbzoj.tk/data/'+prob_num+'.zip'
	gg=os.path.split(os.path.realpath(__file__))[0]
	chromeOptions = webdriver.ChromeOptions()
	prefs = {"download.default_directory": gg}
	chromeOptions.add_experimental_option("prefs", prefs)
	driver = webdriver.Chrome(executable_path="C:\Program Files (x86)\Google\Chrome\Application\chromedriver.exe",\
 	                                 chrome_options=chromeOptions)
	driver.get(url)
	zzz=prob_num+'.zip'
	f=open("_", "w")
	print(zzz, file=f) 