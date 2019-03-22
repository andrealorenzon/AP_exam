import unittest
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

        Parameters
        ----------
        line : str
        '''
        pattern = re.compile("date:(\d*)-(\d*)-(\d*).*from:([^;]+); to:([^;]+);")
        regexItems = re.search(pattern, line)
        
        date = regexItems.group(1) + " " + regexItems.group(2) + " " + regexItems.group(3)
        sender = regexItems.group(4)
        receiver = regexItems.group(5)
        
        return {"sender": sender, "receiver": receiver, "date" : datetime.datetime.strptime(date, "%Y %m %d")}
           
        
    def formatDict(self, infoDict: dict) -> str:
        '''
        It formats a dictionary containing a postcard's information into a string.

        Parameters
        ----------
        infoDict : dict
        '''
        return "date:{}; from:{}; to:{};".format(datetime.datetime.strftime(infoDict["date"],"%Y-%m-%d"), 
                                                   infoDict["sender"], infoDict["receiver"])

    ### End Helper Functions ###
    

    def readFile(self, filename: str):
        """
        It reads the postcards from filename and it stores their information
        in the self._postcards list as dictionaries.

        Parameters
        ----------
        None  
        """
        self._file = filename

        # reset attributes
        self._postcards = []
        self._from = {}
        self._to = {}
        self._date = {}
        self._index = 0 # since every informations previously stored is resetted, the index is too.

        with open(self._file, 'r') as file:
            for line in list(file):
                postcard_dict = self.gatherInfos(line)

                postcard_dict['index'] = self._index # index is added to the postcard dictionary
                self._index += 1

                self._postcards.append(postcard_dict)
             

    def updateLists(self, filename: str):
        """
        It reads the postcards from filename and it stores their information
        in the self._postcards list as dictionaries
      
        Parameters
        ----------
        None  
        """
        self._file = filename

        with open(self._file, 'r') as file:
            for line in list(file):
                postcard_dict = self.gatherInfos(line)
                postcard_dict['index'] = self._index
                self._index += 1
                self._postcards.append(postcard_dict)
        

    def parsePostcards(self):
        '''
        It parses the self._postcards list and updates the self.{_to, _from, _date} dictionaries.

        Parameters
        ----------
        None  
        '''        
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
        '''
        It writes to a file the postcards stored in self._postcards. If the file already exists, 
        it is overwritten.

        Parameters
        ----------
        filename : str
        '''
        with open(filename, 'w') as file:
            for postcard in self._postcards:
                file.write(self.formatDict(postcard) + "\n")
                

    def updateFile(self, filename: str):
        '''
        It writes to a file the postcards stored in self._postcards. If the file already exists, 
        the new content is appended to it.

        Parameters
        ----------
        filename : str
        '''
        with open(filename, 'a') as file:
            for postcard in self._postcards:
                file.write(self.formatDict(postcard) + "\n")
                
    
    def getNumberOfPostcards(self):
        '''
        Returns the number of postcards stored in the self._postcards list.  

        Parameters
        ----------
        None      
        '''
        return len(self._postcards)
    

    def getPostcardsByDateRange(self, date_range: tuple) -> list:
        '''
        Returns the list of postcards sent within a date_range.

        Parameters
        ----------
        date_range : tuple
            It is a tuple of date objects.
        ''' 
        begin, end = date_range
        return [self.formatDict(m) for m in self._postcards if (m["date"] > begin and m["date"] < end)]
        

    def getPostcardsBySender(self, sender: str) -> list: 
        '''
        Returns the list of postcards, formatted as strings, sent by a given sender.

        Parameters
        ----------
        sender : str
        '''    
        return [self.formatDict(m)for m in self._postcards if (m["sender"] == sender)]


    def getPostcardsByReceiver(self, receiver: str) -> list: 
        '''
        Returns the list of postcards, formatted as strings, addressed to a given receiver.

        Parameters
        ----------
        receiver : str
        '''    
        return [self.formatDict(m) for m in self._postcards if (m["receiver"] == receiver)]


########################
# TO COMMENT 
# from exam_solution import PostcardList # overrides the class define above
########################


class Test(unittest.TestCase):

    @classmethod
    def setUpClass(self):
        self._files = ['./exam_postcard_list{}.txt'.format(i) \
                           for i in range(10)]
        self._PstLst = [PostcardList() for f in self._files]
        [p.readFile(f) for f,p in zip(self._files,self._PstLst)]

    def test_missing_attributes(self): 
        attributes_to_define = ['_file','_postcards','_date','_from','_to',\
                                'writeFile','readFile','parsePostcards',\
                                'updateFile','updateLists',\
                                'getNumberOfPostcards',\
                                'getPostcardsByDateRange',\
                                'getPostcardsBySender',\
                                'getPostcardsByReceiver']
        for attr in attributes_to_define:
            if attr not in dir(self._PstLst[0]): 
                raise Exception(attr+' is missing')

    def test_check_getPostcardByDateRange(self): 
        dr_test = []
        for i in [0,1,4,6]: 
            dr_test.append(\
                self._PstLst[i].getPostcardsByDateRange(date_range=\
                   (datetime.datetime.strptime('2008-1-1', "%Y-%m-%d"),\
                    datetime.datetime.strptime('2010-12-31', "%Y-%m-%d"))))
        self.assertListEqual(sorted(dr_test[0]),sorted(['date:2010-06-23; from:Sneezy; to:Alice;\n', 'date:2009-12-12; from:Dopey; to:Peter;\n', 'date:2008-03-23; from:Sneezy; to:Pluto;\n', 'date:2008-06-03; from:Goofy; to:Pluto;\n'])) 
        self.assertEqual(len(dr_test[1]),1)
        self.assertListEqual(sorted(dr_test[2]),sorted(['date:2010-03-30; from:Louie; to:Sneezy;\n', 'date:2010-03-05; from:Goofy; to:Dopey;\n', 'date:2009-11-08; from:Daisy; to:Minnie;\n', 'date:2010-07-13; from:Bashful; to:Louie;\n', 'date:2008-06-29; from:Huey; to:Dopey;\n', 'date:2009-01-04; from:Alice; to:Hook;\n', 'date:2009-04-28; from:Bashful; to:Mickey;\n']))
        self.assertEqual(len(dr_test[3]),7)

    def test_check_getPostcardBySender(self): 
        s_test = []
        for i in [2,3,5,7]:
            for sender in ['Daisy','Bashful','Peter']:
                s_test.append(\
                    self._PstLst[i].getPostcardsBySender(sender=sender))
        self.assertIn('date:2011-12-11; from:Daisy; to:Goofy;\n',s_test[0])
        self.assertListEqual(s_test[1],[])
        self.assertEqual(len(s_test[2]),1)
        self.assertEqual(len(s_test[5]),0)
        self.assertGreater(len(s_test[8]),len(s_test[9]))

    def test_check_getPostcardByReceiver(self): 
        r_test = []
        for i in [0,3,8,9]:
            for receiver in ['Peter','Hook','Alice','SnowWhite']:
                r_test.append(\
                  self._PstLst[i].getPostcardsByReceiver(receiver=receiver))
        self.assertIn('date:2009-12-12; from:Dopey; to:Peter;\n',r_test[0])
        self.assertListEqual(r_test[1],['date:2016-10-23; from:Sneezy; to:Hook;\n'])
        self.assertEqual(len(r_test[2]),2)
        self.assertEqual(len(r_test[6]),3)

    def test_check_sent_received_when(self): 
        srw_test = []
        for ii in range(10):
            for jj in ["Mickey","Minnie","Goofy","Pluto","Donald","Daisy","$crooge","Huey","Dewey","Louie","Peter","Hook","Alice","SnowWhite","Doc","Sleepy","Sneezy","Bashful","Dopey","Happy","Grumpy"]:
                try:
                    srw_test.append(self._PstLst[ii]._from[jj])
                    srw_test.append(self._PstLst[ii]._to[jj])
                    srw_test.append(self._PstLst[ii]._date[jj])
                except: pass
        self.assertListEqual(srw_test[0],[1])
        self.assertListEqual(srw_test[130],[14,25])
        self.assertListEqual(srw_test[138],[10])
        self.assertListEqual(srw_test[140],[15])
        self.assertListEqual(srw_test[192],[13,26])
        self.assertListEqual(srw_test[203],[6, 9, 11, 12, 24, 31, 42])

if __name__ == '__main__':

  unittest.main()