import sqlite3
sqlite_file = 'db.sqlite'
conn = sqlite3.connect(sqlite_file)
c = conn.cursor()
conn.execute("CREATE TABLE measures (timestamp DATETIME, measure INTEGER)")
conn.commit()
conn.close()
