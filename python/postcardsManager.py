import datetime  
import re        #regex

class PostcardList:

    def __init__(self):

        self._file  : str  = ""      # file name, eventually with the full path.
        self._postcards : list = []  # list of postcards (ordereddicts) read from _file.
        self._date    : dict = {}  # a dict where the key is the string date, and the value is a list of indices. Each index refers to the corresponding record.
        self._from    : dict = {}  # is a dict where the key is the string sender, and the value is a list of indices. Each index refers to the corresponding record.
        self._to    : dict = {}  # a dict where the key is the string receiver, and the value is a list of indices. Each index refers to the corresponding record.
        self._index     : int = 0    # index used to identify uniquely each memorised postcard
            
    ### Helper Functions ###
    
    def gatherInfos(self, line: str) -> dict:
        '''
        It converts a string containing a postcard's information to
        a dictionary.
        '''
        pattern = re.compile("date:(\d*)-(\d*)-(\d*).*from:([^;]+); to:([^;]+);")
        regexItems = re.search(pattern, line)
        
        date = regexItems.group(1) + " " + regexItems.group(2) + " " + regexItems.group(3)
        sender = regexItems.group(4)
        receiver = regexItems.group(5)
        
        return {"sender": sender, "receiver": receiver, "date" : datetime.datetime.strptime(date, "%Y %m %d")}
           
        
    def formatDict(self, infoDict: dict) -> str:
        return "date:{}; from:{}; to:{};".format(datetime.datetime.strftime(infoDict["date"],"%Y-%m-%d"), 
                                                   infoDict["sender"], infoDict["receiver"])

    ### End Helper Functions ###
    
    def readFile(self, filename: str):
        """
        It reads the postcards from filename and it stores their information
        in the self._postcards list as dictionaries"""
        self._file = filename

        # reset attributes
        self._postcards = []
        self._from = {}
        self._to = {}
        self._date = {}
        self._index = 0

        with open(self._file, 'r') as file:
            for line in list(file):
                postcard_dict = self.gatherInfos(line)
                postcard_dict['index'] = self._index
                self._index += 1
                self._postcards.append(postcard_dict)
             
    def updateLists(self, filename: str):
        """
        It reads the postcards from filename and it stores their information
        in the self._postcards list as dictionaries"""
        self._file = filename

        with open(self._file, 'r') as file:
            for line in list(file):
                postcard_dict = self.gatherInfos(line)
                postcard_dict['index'] = self._index
                self._index += 1
                self._postcards.append(postcard_dict)
        
    def parsePostcards(self):
        
        for postcard in self._postcards:
            
            p_index = postcard['index']
            p_from = postcard['sender']
            p_to = postcard['receiver']
            p_date = postcard['date']
            
            if p_from in self._from:
                self._from[p_from].append(p_index)
            else:
                self._from[p_from] = [p_index]
                
            if p_to in self._to:
                self._to[p_to].append(p_index)
            else:
                self._to[p_to] = [p_index]
                
            if p_date in self._date:
                self._date[p_date].append(p_index)
            else:
                self._date[p_date] = [p_index]
                
                
    def writeFile(self, filename: str):
        
        with open(filename, 'w') as file:
            for postcard in self._postcards:
                file.write(self.formatDict(postcard) + "\n")
                
    def updateFile(self, filename: str):
        
        with open(filename, 'a') as file:
            for postcard in self._postcards:
                file.write(self.formatDict(postcard) + "\n")
                
    
    def getNumberOfPostcards(self):
        return len(self._postcards)
    
    def getPostcardsByDateRange(self, date_range: tuple) -> list:
        '''
        returns the postcards within a date_range, date_rage is a tuple of 2 date types
        ''' 
        begin = datetime.datetime.strptime(date_range[0], "%Y-%m-%d")
        end = datetime.datetime.strptime(date_range[1], "%Y-%m-%d")
        return [self.formatDict(m) for m in self._postcards if (m["date"] > begin and m["date"] < end)]
        
    def getPostcardsBySender(self, sender: str) -> list: 
        '''
        returns the messages from a sender
        '''    
        return [self.formatDict(m)for m in self._postcards if (m["sender"] == sender)]


    def getPostcardsByReceiver(self, receiver: str) -> list: 
        '''
        returns the postcards to a receiver 
        '''    
        return [self.formatDict(m) for m in self._postcards if (m["receiver"] == receiver)]