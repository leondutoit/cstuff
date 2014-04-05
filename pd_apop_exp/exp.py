# an experiment in search of proof of concept for a hack
# that may just work :)

# section the first: simple in mem db IO with pandas
import pandas as pd
import sqlite3

conn = sqlite3.connect('example.db')

df = pd.DataFrame({
        'x': [i for i in range(10)],
        'y': [i%2 for i in range(10)] })

df.to_sql('exp_table', conn, if_exists = 'append')

res = pd.read_sql('select * from exp_table', conn)

# section the second: the not _so_ simple part...
# execute an apop_model with in mem db data and return df
