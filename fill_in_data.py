import sqlite3
import time
from random import randint
 
sqlite_file = 'db.sqlite'
timestamp_begin = 1388534400  # 01/01/14 00:00
#timestamp_end = timestamp_begin +  60*100
timestamp_end = 1451520000
pitch = 3600
 
try:
    conn = sqlite3.connect(sqlite_file)
    c = conn.cursor()
    timestamp = timestamp_begin
    while timestamp <= timestamp_end:
        print("Iterations left :", (timestamp_end-timestamp)/pitch)
        measure = randint(0, 9)
        conn.execute("INSERT INTO measures (timestamp, measure) VALUES ({timestamp}, {measure})".format(timestamp=timestamp, measure=measure))
        conn.commit()
        timestamp += pitch
except Exception as e:
    conn.rollback()
    raise e
finally:
    conn.close()
