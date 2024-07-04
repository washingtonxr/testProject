from skyfield.api import load, Topos
from datetime import datetime
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

# Load TLE data from Celestrak
#stations_url = 'http://celestrak.com/NORAD/elements/gps-ops.txt'
stations_url = 'http://celestrak.org/NORAD/elements/gp.php?GROUP=beidou&FORMAT=tle'
satellites = load.tle_file(stations_url)
gps_sats = {sat.name: sat for sat in satellites}

# Define observer's location (for example, a known latitude and longitude)
observer = Topos(latitude_degrees=37.7749, longitude_degrees=-122.4194)

# Define the observation time (UTC)
ts = load.timescale()
observation_time = datetime.utcnow()
skyfield_time = ts.utc(observation_time.year, observation_time.month, observation_time.day,
                       observation_time.hour, observation_time.minute, observation_time.second)

# Prepare lists to hold satellite positions
satellite_x = []
satellite_y = []
satellite_z = []
satellite_names = []

# Get the position of each GPS satellite
for name, satellite in gps_sats.items():
    difference = satellite - observer
    topocentric = difference.at(skyfield_time)
    alt, az, distance = topocentric.altaz()

    if alt.degrees > 0:  # Only consider satellites above the horizon
        satellite_names.append(name)
        satellite_x.append(distance.km * np.cos(np.radians(alt.degrees)) * np.cos(np.radians(az.degrees)))
        satellite_y.append(distance.km * np.cos(np.radians(alt.degrees)) * np.sin(np.radians(az.degrees)))
        satellite_z.append(distance.km * np.sin(np.radians(alt.degrees)))

        print(f"Satellite: {name}")
        print(f"Elevation: {alt.degrees} degrees")
        print(f"Azimuth: {az.degrees} degrees")
        print(f"Distance: {distance.km} km")
        print("="*40)

# Plot the satellites in a 3D plot
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Plot the Earth (as a simple sphere)
u = np.linspace(0, 2 * np.pi, 100)
v = np.linspace(0, np.pi, 100)
x = 6371 * np.outer(np.cos(u), np.sin(v))  # Earth radius in km
y = 6371 * np.outer(np.sin(u), np.sin(v))
z = 6371 * np.outer(np.ones(np.size(u)), np.cos(v))
ax.plot_surface(x, y, z, color='b', alpha=0.3)

# Plot the satellites
ax.scatter(satellite_x, satellite_y, satellite_z, c='r', marker='o')

for i, name in enumerate(satellite_names):
    ax.text(satellite_x[i], satellite_y[i], satellite_z[i], name, size=8, zorder=1, color='k')

ax.set_xlabel('X (km)')
ax.set_ylabel('Y (km)')
ax.set_zlabel('Z (km)')
ax.set_title('Satellites Position')

plt.show()

