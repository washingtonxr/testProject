import pandas as pd
import json
df = pd.read_json('../dirRequirements/maxTxPowerForRRM2.json')
# with open('./', 'r') as f:
#     data = json.loads(f.read())

# df = pd.json_normalize(
#     data,
#     record_path=['students'],
#     meta=[
#         'class',
#         ['info', 'president'],
#         ['info', 'contacts', 'tel']
#     ]
# )
print(df)

print(df.to_json())
with open("testToJson.json", 'w') as output_file:
    output_file.write(df.to_json())
