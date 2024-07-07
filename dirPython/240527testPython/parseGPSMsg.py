import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

def parse_gnrmc(sentence):
    parts = sentence.split(',')
    data = {
        'type': parts[0],
        'time': parts[1] if len(parts) > 1 else None,
        'status': parts[2] if len(parts) > 2 else None,
        'latitude': parts[3] if len(parts) > 3 else None,
        'latitude_direction': parts[4] if len(parts) > 4 else None,
        'longitude': parts[5] if len(parts) > 5 else None,
        'longitude_direction': parts[6] if len(parts) > 6 else None,
        'speed': parts[7] if len(parts) > 7 else None,
        'track_angle': parts[8] if len(parts) > 8 else None,
        'date': parts[9] if len(parts) > 9 else None,
        'magnetic_variation': parts[10] if len(parts) > 10 else None,
        'magnetic_variation_direction': parts[11] if len(parts) > 11 else None,
        'mode': parts[12].split('*')[0] if len(parts) > 12 else None
    }
    return data

def parse_gngga(sentence):
    parts = sentence.split(',')
    data = {
        'type': parts[0],
        'time': parts[1] if len(parts) > 1 else None,
        'latitude': parts[2] if len(parts) > 2 else None,
        'latitude_direction': parts[3] if len(parts) > 3 else None,
        'longitude': parts[4] if len(parts) > 4 else None,
        'longitude_direction': parts[5] if len(parts) > 5 else None,
        'fix_quality': parts[6] if len(parts) > 6 else None,
        'num_satellites': parts[7] if len(parts) > 7 else None,
        'horizontal_dilution': parts[8] if len(parts) > 8 else None,
        'altitude': parts[9] if len(parts) > 9 else None,
        'altitude_units': parts[10] if len(parts) > 10 else None,
        'geoid_height': parts[11] if len(parts) > 11 else None,
        'geoid_height_units': parts[12] if len(parts) > 12 else None,
        'time_since_last_dgps_update': parts[13] if len(parts) > 13 else None,
        'dgps_station_id': parts[14].split('*')[0] if len(parts) > 14 else None
    }
    return data

def parse_gpgsa(sentence):
    parts = sentence.split(',')
    data = {
        'type': parts[0],
        'mode': parts[1] if len(parts) > 1 else None,
        'fix_type': parts[2] if len(parts) > 2 else None,
        'satellites_used': parts[3:15] if len(parts) > 15 else parts[3:],
        'pdop': parts[15] if len(parts) > 15 else None,
        'hdop': parts[16] if len(parts) > 16 else None,
        'vdop': parts[17].split('*')[0] if len(parts) > 17 else None
    }
    return data

def parse_bdgsa(sentence):
    return parse_gpgsa(sentence)

def parse_gpgsv(sentence):
    parts = sentence.split(',')
    num_messages = int(parts[1]) if len(parts) > 1 else None
    message_number = int(parts[2]) if len(parts) > 2 else None
    num_satellites = int(parts[3]) if len(parts) > 3 else None
    satellites = []
    print(len(parts))
    for i in range(4, len(parts) - 1, 4):
        satellite = {
            'satellite_id': parts[i] if len(parts) > i else None,
            'elevation': parts[i+1] if len(parts) > i+1 else None,
            'azimuth': parts[i+2] if len(parts) > i+2 else None,
            'snr': int(parts[i+3].split('*')[0]) if len(parts) > i+3 else None
        }
        satellites.append(satellite)
    
    data = {
        'type': parts[0],
        'num_messages': num_messages,
        'message_number': message_number,
        'num_satellites': num_satellites,
        'satellites': satellites
    }
    return data

def parse_bdgsv(sentence):
    return parse_gpgsv(sentence)

def parse_gnvtg(sentence):
    parts = sentence.split(',')
    data = {
        'type': parts[0],
        'track_true': parts[1] if len(parts) > 1 else None,
        'track_true_indicator': parts[2] if len(parts) > 2 else None,
        'track_magnetic': parts[3] if len(parts) > 3 else None,
        'track_magnetic_indicator': parts[4] if len(parts) > 4 else None,
        'speed_knots': parts[5] if len(parts) > 5 else None,
        'speed_knots_indicator': parts[6] if len(parts) > 6 else None,
        'speed_kph': parts[7] if len(parts) > 7 else None,
        'speed_kph_indicator': parts[8].split('*')[0] if len(parts) > 8 else None
    }
    return data

def parse_gngll(sentence):
    parts = sentence.split(',')
    data = {
        'type': parts[0],
        'latitude': parts[1] if len(parts) > 1 else None,
        'latitude_direction': parts[2] if len(parts) > 2 else None,
        'longitude': parts[3] if len(parts) > 3 else None,
        'longitude_direction': parts[4] if len(parts) > 4 else None,
        'time': parts[5] if len(parts) > 5 else None,
        'status': parts[6] if len(parts) > 6 else None,
        'mode': parts[7].split('*')[0] if len(parts) > 7 else None
    }
    return data

def parse_nmea_sentence(sentence):
    parsers = {
        '$GNRMC': parse_gnrmc,
        '$GNGGA': parse_gngga,
        '$GPGSA': parse_gpgsa,
        '$BDGSA': parse_bdgsa,
        '$GPGSV': parse_gpgsv,
        '$BDGSV': parse_bdgsv,
        '$GNVTG': parse_gnvtg,
        '$GNGLL': parse_gngll
    }
    
    sentence_type = sentence.split(',')[0]
    if sentence_type in parsers:
        return parsers[sentence_type](sentence)
    else:
        return None

def draw_position_trajectory(parsed_data):
    latitudes = []
    longitudes = []
    satellite_positions = []

    for data in parsed_data:
        if data['type'] in ['$GNRMC', '$GNGGA', '$GNGLL']:
            latitude = convert_to_decimal_degrees(data['latitude'], data['latitude_direction'])
            longitude = convert_to_decimal_degrees(data['longitude'], data['longitude_direction'])
            latitudes.append(latitude)
            longitudes.append(longitude)
        
        if data['type'] in ['$GPGSV', '$BDGSV']:
            for satellite in data['satellites']:
                if satellite['elevation'] is not None and satellite['azimuth'] is not None and satellite['snr'] is not None:
                    satellite_positions.append((float(satellite['elevation']), float(satellite['azimuth']), satellite['snr']))
    
    fig = plt.figure(figsize=(15, 7))

    # 2D plot for position and trajectory
    ax1 = fig.add_subplot(121)
    ax1.plot(longitudes, latitudes, marker='o')
    ax1.set_title('Position and Trajectory')
    ax1.set_xlabel('Longitude')
    ax1.set_ylabel('Latitude')

    # 3D plot for satellites around the Earth
    ax2 = fig.add_subplot(122, projection='3d')
    earth_radius = 6371  # Earth's radius in kilometers
    num_points = 100
    u = np.linspace(0, 2 * np.pi, num_points)
    v = np.linspace(0, np.pi, num_points)
    x = earth_radius * np.outer(np.cos(u), np.sin(v))
    y = earth_radius * np.outer(np.sin(u), np.sin(v))
    z = earth_radius * np.outer(np.ones(np.size(u)), np.cos(v))
    ax2.plot_surface(x, y, z, color='b', alpha=0.3)

    # Plot satellite positions
    azimuths = [np.radians(pos[1]) for pos in satellite_positions]
    elevations = [np.radians(90 - pos[0]) for pos in satellite_positions]
    snrs = [pos[2] for pos in satellite_positions]
    satellite_x = [earth_radius * np.sin(e) * np.cos(a) for e, a in zip(elevations, azimuths)]
    satellite_y = [earth_radius * np.sin(e) * np.sin(a) for e, a in zip(elevations, azimuths)]
    satellite_z = [earth_radius * np.cos(e) for e in elevations]

    sc = ax2.scatter(satellite_x, satellite_y, satellite_z, c=snrs, cmap='viridis', marker='o')
    fig.colorbar(sc, ax=ax2, label='Signal-to-Noise Ratio (SNR)')
    ax2.set_title('Satellite Positions')
    ax2.set_xlabel('X (km)')
    ax2.set_ylabel('Y (km)')
    ax2.set_zlabel('Z (km)')

    plt.show()

def convert_to_decimal_degrees(value, direction):
    if value is None or direction is None:
        return None
    degrees = float(value[:2])
    minutes = float(value[2:])
    decimal_degrees = degrees + (minutes / 60)
    if direction in ['S', 'W']:
        decimal_degrees = -decimal_degrees
    return decimal_degrees

if __name__ == "__main__":
    # Example usage
    nmea_sentences = [
        "$GNRMC,123519,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*6A",
        "$GNGGA,123520,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47",
        "$GPGSA,A,3,04,05,,09,12,,,,,1.8,1.0,1.2*30",
        "$BDGSA,A,3,04,05,,09,12,,,,,1.8,1.0,1.2*30",
        "$GPGSV,2,1,08,01,40,083,41,02,50,057,42,03,60,029,43,04,70,301,44*71",
        "$BDGSV,2,1,08,01,40,083,41,02,50,057,42,03,60,029,43,04,70,301,44*71",
        "$GNVTG,054.7,T,034.4,M,005.5,N,010.2,K*48",
        "$GNGLL,4916.45,N,12311.12,W,225444,A,*1D"
    ]

    nmea_sentences2 = [
        "$GNGLL,2652.9236,N,12000.3646,E,012414.00,A,D*79",
        "$GNRMC,012415.00,A,2652.9236,N,12000.3646,E,0.000,011.4,020624,,,D*49",
        "$GNGGA,012415.00,2652.9236,N,12000.3646,E,2,16,0.7,31.1,M,11.2,M,,*4A",
        "$GPGSA,A,3,08,03,17,06,14,30,21,,,,,,1.6,0.7,1.4*39",
        "$BDGSA,A,3,01,04,11,23,28,16,14,25,07,,,,1.6,0.7,1.4*2A",
        "$GPGSV,3,1,12,02,41,034,23,03,43,119,44,06,17,229,35,08,11,079,27*78",
        "$GPGSV,3,2,12,14,62,328,31,17,39,309,35,21,25,040,30,22,38,323,24*7D",
        "$GPGSV,3,3,12,30,37,234,30,50,57,164,48,07,25,197,,19,18,286,*71",
        "$BDGSV,4,1,16,01,48,135,44,03,55,199,34,04,36,118,35,05,16,254,28*61",
        "$BDGSV,4,2,16,06,26,207,24,07,62,341,35,09,33,222,27,10,51,319,23*6A",
        "$BDGSV,4,3,16,11,29,042,36,14,17,119,40,16,24,202,27,23,65,223,45*6A",
        "$BDGSV,4,4,16,25,26,165,29,28,44,283,32,02,37,235,,08,31,178,*61",
        "$GNVTG,011.4,T,,,0.000,N,0.000,K,D*5F",
        "$GNGLL,2652.9236,N,12000.3646,E,012415.00,A,D*78",
        "$GNRMC,012416.00,A,2652.9236,N,12000.3646,E,0.000,011.4,020624,,,D*4A",
        "$GNGGA,012416.00,2652.9236,N,12000.3646,E,2,16,0.7,31.1,M,11.2,M,,*49",
        "$GPGSA,A,3,08,03,17,06,14,30,21,,,,,,1.6,0.7,1.4*39",
        "$BDGSA,A,3,01,04,11,23,28,16,14,25,07,,,,1.6,0.7,1.4*2A",
        "$GPGSV,3,1,12,02,41,034,22,03,43,119,44,06,17,229,35,08,11,079,27*79",
        "$GPGSV,3,2,12,14,62,328,31,17,39,309,35,21,25,040,31,22,39,323,24*7D",
        "$GPGSV,3,3,12,30,37,234,30,50,57,164,47,07,25,197,,19,18,286,*7E",
        "$BDGSV,4,1,16,01,48,135,44,03,55,199,35,04,36,118,35,05,16,254,28*60",
        "$BDGSV,4,2,16,06,26,207,24,07,62,341,35,09,33,222,27,10,51,319,24*6D",
        "$BDGSV,4,3,16,11,29,042,36,14,17,119,39,16,24,202,27,23,65,223,45*64",
        "$BDGSV,4,4,16,25,26,165,29,28,44,283,32,02,37,235,,08,31,178,*61",
        "$GNVTG,011.4,T,,,0.000,N,0.000,K,D*5F",
        "$GNGLL,2652.9236,N,12000.3646,E,012416.00,A,D*7B",
        "$GNRMC,012417.00,A,2652.9236,N,12000.3646,E,0.000,011.4,020624,,,D*4B",
        "$GNGGA,012417.00,2652.9236,N,12000.3646,E,2,16,0.7,31.1,M,11.2,M,,*48",
        "$GPGSA,A,3,08,03,17,06,14,30,21,,,,,,1.6,0.7,1.4*39",
        "$BDGSA,A,3,01,04,11,09,23,28,14,25,07,,,,1.6,0.7,1.4*24",
        "$GPGSV,3,1,12,02,41,034,22,03,43,119,45,06,17,229,35,08,11,079,27*78",
        "$GPGSV,3,2,12,14,62,328,30,17,39,309,35,21,25,040,31,22,39,323,24*7C",
        "$GPGSV,3,3,12,30,37,234,30,50,57,164,48,07,25,197,,19,18,286,*71",
        "$BDGSV,4,1,16,01,48,135,44,03,55,199,35,04,36,118,35,05,16,254,28*60",
        "$BDGSV,4,2,16,06,26,207,24,07,62,341,35,09,33,222,27,10,51,319,24*6D",
        "$BDGSV,4,3,16,11,29,042,36,14,17,119,40,16,24,202,26,23,65,223,45*6B",
        "$BDGSV,4,4,16,25,26,165,29,28,44,283,32,02,37,235,,08,31,178,*61",
        "$GNVTG,011.4,T,,,0.000,N,0.000,K,D*5F",
        "$GNGLL,2652.9236,N,12000.3646,E,012417.00,A,D*7A",
        "$GNRMC,012418.00,A,2652.9236,N,12000.3646,E,0.000,011.4,020624,,,D*44",
        "$GNGGA,012418.00,2652.9236,N,12000.3646,E,2,16,0.7,31.1,M,11.2,M,,*47",
        "$GPGSA,A,3,08,03,17,06,14,30,21,,,,,,1.6,0.7,1.4*39",
        "$BDGSA,A,3,01,04,11,23,28,16,14,25,07,,,,1.6,0.7,1.4*2A",
        "$GPGSV,3,1,12,02,41,034,22,03,43,119,45,06,17,229,35,08,11,079,27*78",
        "$GPGSV,3,2,12,14,62,328,30,17,39,309,35,21,25,040,31,22,39,323,24*7C",
        "$GPGSV,3,3,12,30,37,234,30,50,57,164,47,07,25,197,,19,18,286,*7E",
        "$BDGSV,4,1,16,01,48,135,44,03,55,199,35,04,36,118,35,05,16,254,28*60",
        "$BDGSV,4,2,16,06,26,207,24,07,62,341,35,09,33,222,27,10,51,319,24*6D",
        "$BDGSV,4,3,16,11,29,042,36,14,17,119,40,16,24,202,26,23,65,223,45*6B",
        "$BDGSV,4,4,16,25,26,165,29,28,44,283,32,02,37,235,,08,31,178,*61",
        "$GNVTG,011.4,T,,,0.000,N,0.000,K,D*5F",
        "$GNGLL,2652.9236,N,12000.3646,E,012418.00,A,D*75",
        "$GNRMC,012419.00,A,2652.9236,N,12000.3646,E,0.000,011.4,020624,,,D*45",
        "$GNGGA,012419.00,2652.9236,N,12000.3646,E,2,16,0.7,31.1,M,11.2,M,,*46",
        "$GPGSA,A,3,08,03,17,06,14,30,21,,,,,,1.6,0.7,1.4*39",
        "$BDGSA,A,3,01,04,11,09,23,28,14,25,07,,,,1.6,0.7,1.4*24",
        "$GPGSV,3,1,12,02,41,034,21,03,43,119,45,06,17,229,35,08,11,079,27*7B",
        "$GPGSV,3,2,12,14,62,328,30,17,39,309,35,21,25,040,31,22,39,323,24*7C",
        "$GPGSV,3,3,12,30,37,234,30,50,57,164,47,07,25,197,,19,18,286,*7E",
        "$BDGSV,4,1,16,01,48,135,44,03,55,199,35,04,36,118,35,05,16,254,28*60",
        "$BDGSV,4,2,16,06,26,207,24,07,62,341,35,09,33,222,27,10,51,319,24*6D",
        "$BDGSV,4,3,16,11,29,042,36,14,17,119,40,16,24,202,26,23,65,223,46*68",
        "$BDGSV,4,4,16,25,26,165,29,28,44,283,32,02,37,235,,08,31,178,*61",
        "$GNVTG,011.4,T,,,0.000,N,0.000,K,D*5F",
        "$GNGLL,2652.9236,N,12000.3646,E,012419.00,A,D*74",
        "$GNRMC,012420.00,A,2652.9236,N,12000.3646,E,0.000,011.4,020624,,,D*4F",
        "$GNGGA,012420.00,2652.9236,N,12000.3646,E,2,16,0.7,31.1,M,11.2,M,,*4C",
        "$GPGSA,A,3,08,03,17,06,14,30,21,,,,,,1.6,0.7,1.4*39",
        "$BDGSA,A,3,01,04,11,23,28,16,14,25,07,,,,1.6,0.7,1.4*2A",
        "$GPGSV,3,1,12,02,41,034,21,03,43,119,45,06,17,229,35,08,11,079,27*7B",
        "$GPGSV,3,2,12,14,62,328,30,17,39,309,35,21,25,040,32,22,39,323,24*7F",
        "$GPGSV,3,3,12,30,37,234,30,50,57,164,48,07,25,197,,19,18,286,*71",
        "$BDGSV,4,1,16,01,48,135,44,03,55,199,35,04,36,118,35,05,16,254,28*60",
        "$BDGSV,4,2,16,06,26,207,24,07,62,341,35,09,33,222,27,10,51,319,24*6D",
        "$BDGSV,4,3,16,11,29,042,36,14,17,119,40,16,24,202,27,23,65,223,46*69",
        "$BDGSV,4,4,16,25,26,165,30,28,44,283,32,02,37,235,,08,31,178,*69",
        "$GNVTG,011.4,T,,,0.000,N,0.000,K,D*5F",
        "$GNGLL,2652.9236,N,12000.3646,E,012420.00,A,D*7E",
        "$GNRMC,012421.00,A,2652.9236,N,12000.3646,E,0.000,011.4,020624,,,D*4E",
        "$GNGGA,012421.00,2652.9236,N,12000.3646,E,2,16,0.7,31.1,M,11.2,M,,*4D",
        "$GPGSA,A,3,03,17,06,14,30,21,,,,,,,1.6,0.7,1.5*30",
        "$BDGSA,A,3,01,04,11,09,23,28,16,14,25,07,,,1.6,0.7,1.5*22",
        "$GPGSV,3,1,12,02,41,034,20,03,43,119,45,06,17,229,35,08,11,079,27*7A",
        "$GPGSV,3,2,12,14,62,328,31,17,39,309,35,21,25,040,32,22,39,323,24*7E",
        "$GPGSV,3,3,12,30,37,233,30,50,57,164,48,07,25,197,,19,18,286,*76",
        "$BDGSV,4,1,16,01,48,135,44,03,55,199,34,04,36,118,35,05,16,254,28*61",
        "$BDGSV,4,2,16,06,26,207,24,07,62,341,35,09,33,222,27,10,51,319,24*6D",
        "$BDGSV,4,3,16,11,29,042,36,14,17,119,40,16,24,202,26,23,65,223,46*68",
        "$BDGSV,4,4,16,25,26,165,30,28,44,283,32,02,37,235,,08,31,178,*69",
        "$GNVTG,011.4,T,,,0.000,N,0.000,K,D*5F",
        "$GNGLL,2652.9236,N,12000.3646,E,012421.00,A,D*7F",
        "$GNRMC,012422.00,A,2652.9236,N,12000.3646,E,0.000,011.4,020624,,,D*4D",
        "$GNGGA,012422.00,2652.9236,N,12000.3646,E,2,16,0.7,31.1,M,11.2,M,,*4E",
        "$GPGSA,A,3,08,03,17,06,14,30,21,,,,,,1.6,0.7,1.4*39",
        "$BDGSA,A,3,01,04,11,23,28,16,14,25,07,,,,1.6,0.7,1.4*2A",
        "$GPGSV,3,1,12,02,41,034,19,03,43,119,45,06,17,229,35,08,11,079,27*70",
        "$GPGSV,3,2,12,14,62,328,30,17,39,309,35,21,25,040,32,22,39,323,24*7F",
        "$GPGSV,3,3,12,30,37,233,30,50,57,164,48,07,25,197,,19,18,286,*76",
        "$BDGSV,4,1,16,01,48,135,44,03,55,199,35,04,36,118,35,05,16,254,28*60",
        "$BDGSV,4,2,16,06,26,207,24,07,62,341,35,09,33,222,27,10,51,319,24*6D",
        "$BDGSV,4,3,16,11,29,042,36,14,17,119,40,16,24,202,26,23,65,223,46*68",
        "$BDGSV,4,4,16,25,26,165,29,28,44,283,31,02,37,235,,08,31,178,*62",
        "$GNVTG,011.4,T,,,0.000,N,0.000,K,D*5F",
        "$GNGLL,2652.9236,N,12000.3646,E,012422.00,A,D*7C",
        "$GNRMC,012423.00,A,2652.9236,N,12000.3646,E,0.000,011.4,020624,,,D*4C",
        "$GNGGA,012423.00,2652.9236,N,12000.3646,E,2,16,0.7,31.1,M,11.2,M,,*4F",
        "$GPGSA,A,3,03,17,06,14,30,21,,,,,,,1.6,0.7,1.5*30",
        "$BDGSA,A,3,01,04,11,09,23,28,16,14,25,07,,,1.6,0.7,1.5*22",
        "$GPGSV,3,1,12,02,41,034,19,03,43,119,45,06,17,229,35,08,11,079,26*71",
        "$GPGSV,3,2,12,14,62,328,30,17,39,309,36,21,25,040,33,22,39,323,24*7D",
        "$GPGSV,3,3,12,30,37,233,30,50,57,164,48,07,25,197,,19,18,286,*76",
        "$BDGSV,4,1,16,01,48,135,44,03,55,199,34,04,36,118,35,05,16,254,28*61",
        "$BDGSV,4,2,16,06,26,207,24,07,62,341,35,09,33,222,27,10,51,319,24*6D",
        "$BDGSV,4,3,16,11,29,042,36,14,17,119,40,16,24,202,26,23,65,223,46*68",
        "$BDGSV,4,4,16,25,26,165,29,28,44,283,31,02,37,235,,08,31,178,*62",
        "$GNVTG,011.4,T,,,0.000,N,0.000,K,D*5F",
        "$GNGLL,2652.9236,N,12000.3646,E,012423.00,A,D*7D",
        "$GNRMC,012424.00,A,2652.9236,N,12000.3646,E,0.000,011.4,020624,,,D*4B",
        "$GNGGA,012424.00,2652.9236,N,12000.3646,E,2,16,0.7,31.1,M,11.2,M,,*48",
        "$GPGSA,A,3,03,17,06,14,30,21,,,,,,,1.6,0.7,1.5*30",
        "$BDGSA,A,3,01,04,11,09,23,28,16,14,25,07,,,1.6,0.7,1.5*22",
        "$GPGSV,3,1,12,02,41,034,18,03,43,119,45,06,17,229,34,08,11,079,26*71",
        "$GPGSV,3,2,12,14,62,328,30,17,39,309,36,21,25,040,33,22,39,323,24*7D",
        "$GPGSV,3,3,12,30,37,233,30,50,57,164,48,07,25,197,,19,18,286,*76",
        "$BDGSV,4,1,16,01,48,135,44,03,55,199,35,04,36,118,35,05,16,254,28*60",
        "$BDGSV,4,2,16,06,26,207,24,07,62,341,35,09,33,222,27,10,51,319,24*6D",
        "$BDGSV,4,3,16,11,29,042,36,14,17,119,40,16,24,202,26,23,65,223,46*68",
        "$BDGSV,4,4,16,25,26,165,29,28,44,283,31,02,37,235,,08,31,178,*62",
        "$GNVTG,011.4,T,,,0.000,N,0.000,K,D*5F",
        "$GNGLL,2652.9236,N,12000.3646,E,012424.00,A,D*7A",
        "$GNRMC,012425.00,A,2652.9236,N,12000.3646,E,0.000,011.4,020624,,,D*4A",
        "$GNGGA,012425.00,2652.9236,N,12000.3646,E,2,16,0.7,31.1,M,11.2,M,,*49",
        "$GPGSA,A,3,08,03,17,06,14,30,21,,,,,,1.6,0.7,1.4*39",
        "$BDGSA,A,3,01,04,11,09,23,28,14,25,07,,,,1.6,0.7,1.4*24",
        "$GPGSV,3,1,12,02,41,034,18,03,43,119,45,06,17,229,34,08,11,079,26*71",
        "$GPGSV,3,2,12,14,62,328,30,17,39,309,36,21,25,040,33,22,39,323,23*7A",
        "$GPGSV,3,3,12,30,37,233,30,50,57,164,48,07,25,197,,19,18,286,*76",
        "$BDGSV,4,1,16,01,48,135,45,03,55,199,35,04,36,118,35,05,16,254,28*61",
        "$BDGSV,4,2,16,06,26,207,24,07,62,341,35,09,33,222,27,10,51,319,24*6D",
        "$BDGSV,4,3,16,11,29,042,36,14,17,119,40,16,24,202,27,23,65,223,47*68",
        "$BDGSV,4,4,16,25,26,165,29,28,44,283,31,02,37,235,,08,31,178,*62",
        "$GNVTG,011.4,T,,,0.000,N,0.000,K,D*5F",
        "$GNGLL,2652.9236,N,12000.3646,E,012425.00,A,D*7B",
        "$GNRMC,012426.00,A,2652.9236,N,12000.3646,E,0.000,011.4,020624,,,D*49",
        "$GNGGA,012426.00,2652.9236,N,12000.3646,E,2,16,0.7,31.1,M,11.2,M,,*4A",
        "$GPGSA,A,3,03,17,06,14,30,21,,,,,,,1.6,0.7,1.5*30",
        "$BDGSA,A,3,01,04,11,09,23,28,16,14,25,07,,,1.6,0.7,1.5*22",
        "$GPGSV,3,1,12,02,41,034,17,03,43,119,45,06,17,229,35,08,11,079,26*7F",
        "$GPGSV,3,2,12,14,62,328,30,17,39,309,36,21,25,040,33,22,39,323,23*7A",
        "$GPGSV,3,3,12,30,37,233,30,50,57,164,48,07,25,197,,19,18,286,*76",
        "$BDGSV,4,1,16,01,48,135,44,03,55,199,34,04,36,118,35,05,16,254,28*61",
        "$BDGSV,4,2,16,06,26,207,24,07,62,341,36,09,33,222,27,10,51,319,24*6E",
        "$BDGSV,4,3,16,11,29,042,36,14,17,119,40,16,24,202,27,23,65,223,47*68",
        "$BDGSV,4,4,16,25,26,165,29,28,44,283,31,02,37,235,,08,31,178,*62",
        "$GNVTG,011.4,T,,,0.000,N,0.000,K,D*5F",
        "$GNGLL,2652.9236,N,12000.3646,E,012426.00,A,D*78",
        "$GNRMC,012427.00,A,2652.9236,N,12000.3646,E,0.000,011.4,020624,,,D*48",
        "$GNGGA,012427.00,2652.9236,N,12000.3646,E,2,16,0.7,31.1,M,11.2,M,,*4B",
        "$GPGSA,A,3,08,03,17,06,14,30,21,,,,,,1.6,0.7,1.4*39",
        "$BDGSA,A,3,01,04,11,23,28,16,14,25,07,,,,1.6,0.7,1.4*2A",
        "$GPGSV,3,1,12,02,41,034,17,03,43,119,45,06,18,229,35,08,11,079,26*70",
        "$GPGSV,3,2,12,14,62,328,30,17,39,309,36,21,25,040,33,22,39,323,23*7A",
        "$GPGSV,3,3,12,30,37,233,30,50,57,164,48,07,25,197,,19,18,286,*76",
        "$BDGSV,4,1,16,01,48,135,44,03,55,199,35,04,36,118,35,05,16,254,28*60",
        "$BDGSV,4,2,16,06,26,207,24,07,62,341,36,09,33,222,27,10,51,319,24*6E",
        "$BDGSV,4,3,16,11,29,042,36,14,17,119,40,16,24,202,27,23,65,222,46*68",
        "$BDGSV,4,4,16,25,26,165,29,28,44,283,31,02,37,235,,08,31,178,*62",
        "$GNVTG,011.4,T,,,0.000,N,0.000,K,D*5F",
        "$GNGLL,2652.9236,N,12000.3646,E,012427.00,A,D*79",
        "$GNRMC,012428.00,A,2652.9236,N,12000.3646,E,0.000,011.4,020624,,,D*47",
        "$GNGGA,012428.00,2652.9236,N,12000.3646,E,2,16,0.7,31.1,M,11.2,M,,*44",
        "$GPGSA,A,3,08,03,17,06,14,30,21,,,,,,1.6,0.7,1.4*39",
        "$BDGSA,A,3,01,04,11,09,23,28,14,25,07,,,,1.6,0.7,1.4*24",
        "$GPGSV,3,1,12,02,41,034,15,03,43,119,45,06,18,229,35,08,11,079,27*73",
        "$GPGSV,3,2,12,14,62,328,30,17,39,309,36,21,25,040,33,22,39,323,23*7A",
        "$GPGSV,3,3,12,30,37,233,30,50,57,164,48,07,25,197,,19,18,286,*76",
        "$BDGSV,4,1,16,01,48,135,44,03,55,199,34,04,36,118,35,05,16,254,28*61",
        "$BDGSV,4,2,16,06,26,207,23,07,62,341,36,09,33,222,27,10,51,319,24*69",
        "$BDGSV,4,3,16,11,29,042,36,14,17,119,40,16,24,202,27,23,65,222,47*69",
        "$BDGSV,4,4,16,25,26,165,29,28,44,283,31,02,37,235,,08,31,178,*62",
        "$GNVTG,011.4,T,,,0.000,N,0.000,K,D*5F",
        "$GNGLL,2652.9236,N,12000.3646,E,012428.00,A,D*76",
        "$GNRMC,012429.00,A,2652.9236,N,12000.3646,E,0.000,011.4,020624,,,D*46",
        "$GNGGA,012429.00,2652.9236,N,12000.3646,E,2,16,0.7,31.1,M,11.2,M,,*45",
        "$GPGSA,A,3,03,17,06,14,30,21,,,,,,,1.6,0.7,1.5*30",
        "$BDGSA,A,3,01,04,11,09,23,28,16,14,25,07,,,1.6,0.7,1.5*22",
        "$GPGSV,3,1,12,02,41,034,12,03,43,119,45,06,18,229,35,08,11,079,26*75",
        "$GPGSV,3,2,12,14,62,328,30,17,39,309,36,21,25,040,33,22,39,323,24*7D",
        "$GPGSV,3,3,12,30,37,233,30,50,57,164,48,07,25,197,,19,18,286,*76",
        "$BDGSV,4,1,16,01,48,135,44,03,55,199,34,04,36,118,35,05,16,254,28*61",
        "$BDGSV,4,2,16,06,26,207,23,07,62,341,36,09,33,222,27,10,51,319,24*69",
        "$BDGSV,4,3,16,11,29,042,35,14,17,119,40,16,24,202,27,23,65,222,47*6A",
        "$BDGSV,4,4,16,25,26,165,29,28,44,283,32,02,37,235,,08,31,178,*61",
        "$GNVTG,011.4,T,,,0.000,N,0.000,K,D*5F",
        "$GNGLL,2652.9236,N,12000.3646,E,012429.00,A,D*77",
        "$GNRMC,012430.00,A,2652.9236,N,12000.3646,E,0.000,011.4,020624,,,D*4E",
        "$GNGGA,012430.00,2652.9236,N,12000.3646,E,2,16,0.7,31.1,M,11.2,M,,*4D",
        "$GPGSA,A,3,03,17,06,14,30,21,,,,,,,1.6,0.7,1.5*30",
        "$BDGSA,A,3,01,04,11,09,23,28,16,14,25,07,,,1.6,0.7,1.5*22",
        "$GPGSV,3,1,12,02,41,034,10,03,43,119,46,06,18,229,35,08,11,079,26*74",
        "$GPGSV,3,2,12,14,62,328,31,17,39,309,36,21,25,040,33,22,39,323,24*7C",
        "$GPGSV,3,3,12,30,37,233,30,50,57,164,48,07,25,197,,19,18,286,*76",
        "$BDGSV,4,1,16,01,48,135,45,03,55,199,34,04,36,118,35,05,16,254,28*60",
        "$BDGSV,4,2,16,06,26,207,23,07,62,341,36,09,33,222,27,10,51,319,24*69",
        "$BDGSV,4,3,16,11,29,042,36,14,17,119,40,16,24,202,27,23,65,222,47*69",
        "$BDGSV,4,4,16,25,26,165,29,28,44,283,32,02,37,235,,08,31,178,*61",
        "$GNVTG,011.4,T,,,0.000,N,0.000,K,D*5F",
        "$GNGLL,2652.9236,N,12000.3646,E,012430.00,A,D*7F",
        "$GNRMC,012431.00,A,2652.9236,N,12000.3646,E,0.000,011.4,020624,,,D*4F",
        "$GNGGA,012431.00,2652.9236,N,12000.3646,E,2,16,0.7,31.1,M,11.2,M,,*4C",
        "$GPGSA,A,3,03,17,06,14,30,21,,,,,,,1.6,0.7,1.5*30",
        "$BDGSA,A,3,01,04,11,09,23,28,16,14,25,07,,,1.6,0.7,1.5*22",
        "$GPGSV,3,1,12,02,41,034,08,03,43,119,46,06,18,229,34,08,11,079,26*7C",
        "$GPGSV,3,2,12,14,62,328,31,17,39,309,36,21,25,040,33,22,39,323,24*7C",
        "$GPGSV,3,3,12,30,37,233,30,50,57,164,48,07,25,197,,19,18,286,*76",
        "$BDGSV,4,1,16,01,48,135,45,03,55,199,34,04,36,118,35,05,16,254,28*60",
        "$BDGSV,4,2,16,06,26,207,23,07,62,341,35,09,33,222,27,10,51,319,24*6A",
        "$BDGSV,4,3,16,11,29,042,36,14,17,119,40,16,24,202,27,23,65,222,47*69",
        "$BDGSV,4,4,16,25,26,165,29,28,44,283,32,02,37,235,,08,31,178,*61",
        "$GNVTG,011.4,T,,,0.000,N,0.000,K,D*5F",
        "$GNGLL,2652.9236,N,12000.3646,E,012431.00,A,D*7E",
        "$GNRMC,012432.00,A,2652.9236,N,12000.3646,E,0.000,011.4,020624,,,D*4C",
        "$GNGGA,012432.00,2652.9236,N,12000.3646,E,2,16,0.7,31.1,M,11.2,M,,*4F",
        "$GPGSA,A,3,03,17,06,14,30,21,,,,,,,1.6,0.7,1.5*30",
        "$BDGSA,A,3,01,04,11,09,23,28,16,14,25,07,,,1.6,0.7,1.5*22",
        "$GPGSV,3,1,12,02,41,034,08,03,43,119,46,06,18,229,34,08,11,079,26*7C",
        "$GPGSV,3,2,12,14,62,328,30,17,39,309,36,21,25,040,34,22,39,323,24*7A",
        "$GPGSV,3,3,12,30,37,233,29,50,57,164,48,07,25,197,,19,18,286,*7E",
        "$BDGSV,4,1,16,01,48,135,44,03,55,199,34,04,36,118,35,05,16,254,28*61",
        "$BDGSV,4,2,16,06,26,207,23,07,62,341,35,09,33,222,27,10,51,319,24*6A",
        "$BDGSV,4,3,16,11,29,042,36,14,17,119,40,16,24,202,27,23,65,222,46*68",
        "$BDGSV,4,4,16,25,26,165,29,28,44,283,32,02,37,235,,08,31,178,*61",
        "$GNVTG,011.4,T,,,0.000,N,0.000,K,D*5F",
        "$GNGLL,2652.9236,N,12000.3646,E,012432.00,A,D*7D",
        "$GNRMC,012433.00,A,2652.9236,N,12000.3646,E,0.000,011.4,020624,,,D*4D",
        "$GNGGA,012433.00,2652.9236,N,12000.3646,E,2,16,0.7,31.1,M,11.2,M,,*4E",
        "$GPGSA,A,3,03,17,06,14,30,21,,,,,,,1.6,0.7,1.5*30",
        "$BDGSA,A,3,01,04,11,09,23,28,16,14,25,07,,,1.6,0.7,1.5*22",
        "$GPGSV,3,1,12,02,41,034,08,03,43,119,45,06,18,229,34,08,11,079,26*7F",
        "$GPGSV,3,2,12,14,62,328,31,17,39,309,36,21,25,040,34,22,39,323,25*7A",
        "$GPGSV,3,3,12,30,37,233,29,50,57,164,48,07,25,197,,19,18,286,*7E",
        "$BDGSV,4,1,16,01,48,135,44,03,55,199,35,04,36,118,35,05,16,254,28*60",
        "$BDGSV,4,2,16,06,26,207,24,07,62,341,35,09,33,222,27,10,51,319,25*6C",
        "$BDGSV,4,3,16,11,29,042,36,14,17,119,40,16,24,202,27,23,65,222,47*69",
        "$BDGSV,4,4,16,25,26,165,29,28,44,283,32,02,37,235,,08,31,178,*61",
        "$GNVTG,011.4,T,,,0.000,N,0.000,K,D*5F"
    ]

    parsed_data = []
    for sentence in nmea_sentences2:
        parsed_sentence = parse_nmea_sentence(sentence)
        if parsed_sentence:
            parsed_data.append(parsed_sentence)
            print(parsed_sentence)

    draw_position_trajectory(parsed_data)